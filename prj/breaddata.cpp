#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "breaddata.h"
#include "resultwnd.h"
#include <QMessageBox>
#include <QApplication>
#include <QMainWindow>
#include <QtWidgets>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cmath>

breadData::breadData(std::string fileIn):
    finalWhite(0),
    finalWheat(0),
    RND_UP(false),
    stcksPerBox(30),
    rndSticksTo(4),
    whiteLeft(30),
    wheatLeft(30),
    bckUpWhite(30),
    bckUpWheat(30),
    breadCost(18.5),
    fin(NULL)
{
    for(int i=0; i<WEEK_COUNT;i++)              //reserve 7 spaces
        dailySales.push_back(1000);             //default sales estimate set at 1000
    fileName = fileIn;                          //set file name
}

breadData::~breadData()
{
    if(fin != NULL)                         //deleting uninit object will SEG FAULT LIKA BITCH
        delete fin;                         //free result window
}

//pretty much the real cntr
void breadData::_brdLink(QMainWindow *linker, Ui::MainWindow *ui)
{
    mainWnd = linker;           //mainWnd is used to display messagebox's and limited external control of window
    usI = ui;                   //grab a copy of the UI for manipulation
    fin = new resultWnd(mainWnd);
    fin->hide();                //dont show it yet goddammit
}

void breadData::writeData()
{
    std::ofstream writeOut;
    writeOut.open("format.dat");
    if(!writeOut.is_open()){            //never happens unless someone gets real retarded like`
        QMessageBox::critical(mainWnd,QMainWindow::tr("Error_writeData()"),QMainWindow::tr("Could not open file to write"));
        return;
    }
    //write all data to file in given format
    writeOut << "ROUNDUP\n";
    if(RND_UP)
        writeOut << "TRUE\n";
    else
        writeOut << "FALSE\n";
    writeOut << "\nDAILYSALES\n";
    for(int i=0; i<7;i++)
        writeOut << dailySales.at(i) << " ";
    writeOut << "\n\nBREADPERBOX\n" << stcksPerBox << "\n";
    writeOut << "\nBREADRNDUP\n" << rndSticksTo << "\n";
    writeOut << "\nWHITEWHEATLEFT\n" << whiteLeft << " " << wheatLeft << "\n";
    writeOut << "\nBCKUP\n" << bckUpWhite << " " << bckUpWheat << "\n";
    writeOut << "\nBRDCONST\n" << breadCost << "\n";
    writeOut.close();
}


bool breadData::readData()
{
    std::string readTMP;                        //temp string to grab file data
    std::ifstream inFile(fileName.c_str());     //open file to read
    if(!inFile.is_open()) {                     //if the file cannot be read, critical message and return false
        if(QMessageBox::question(mainWnd,QMainWindow::tr("Data not found"),QMainWindow::tr("The application could not find format.dat, would you like to create a new data set?"),QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
            writeData();
        else
            return false;
    }
    while(inFile >> readTMP) {

        if(readTMP == "ROUNDUP"){               //rounding up with sticks
            inFile >> readTMP;
            if(readTMP == "TRUE")
                RND_UP = true;
            else
                RND_UP = false;
        }
        if(readTMP == "DAILYSALES"){            //projected sales for the week
            for(int i = 0; i < 7; i++){
                int projectedSales;
                inFile >> projectedSales;
                dailySales.at(i) = projectedSales;
            }
        }
        if(readTMP == "BREADPERBOX"){           //sticks per box
            inFile >> stcksPerBox;
        }
        if(readTMP == "BREADRNDUP"){            //round stick count to the nearest
            inFile >> rndSticksTo;
        }
        if(readTMP == "WHITEWHEATLEFT"){        //sticks left in freezer
            inFile >> whiteLeft >> wheatLeft;
        }
        if(readTMP == "BRDCONST"){              //bread cost
            inFile >> breadCost;
        }
        if(readTMP == "BCKUP"){                 //back up for sticks left(revert purposes)
            inFile >> bckUpWhite >> bckUpWheat;
        }
    }
    inFile.close();
    return true;
}

void breadData::gatherInput(STATE IS)
{
    //wrap if statement to make sure these are set. IF NOT THE PROGRAM WILL FUCKING EXPLODE
    if(usI != NULL && mainWnd != NULL){
    switch(IS) {
        //no cater
        case NONE:
            //stick count for use with algorithm
            whiteSticks = usI->whiteIN->value();
            wheatSticks = usI->wheatIN->value();
        break;
        //mixed bread 1 IN
        case MIXED:
            whiteSticks = usI->whiteIN->value() - ceil(usI->whiteCIN->value() / 4.0);
            wheatSticks = usI->wheatIN->value() - ceil(usI->whiteCIN->value() / 4.0);
        break;
        //custom 2 IN
        case CUSTOM:
            whiteSticks = usI->whiteIN->value() - usI->whiteCIN->value();
            wheatSticks = usI->wheatIN->value() - usI->wheatCIN->value();
        break;
    }}else
        QMessageBox::critical(mainWnd,QMainWindow::tr("Error_gatherInput()"),QMainWindow::tr("BreadOBJ not is not linked FATAL"));
}

void breadData::calculateBread()
{
    time_t t = time(0);
    struct tm * now = localtime(&t);        //grab local time from system
    int dayIndex = now->tm_wday;            //days since sunday(0-6)

    //proj sales divded by breadcost split for both white and wheat
    double bread = static_cast<double>(dailySales.at(dayIndex)) / (breadCost * 2.0);

    int intpart = (int)bread;
    double decpart = bread - intpart;
    //round bread to nearest whole number
    bread = decpart < 0.5 ? floor(bread) : ceil(bread);

    finalWhite = round((int)bread - whiteSticks);
    finalWheat = round((int)bread - wheatSticks);

    bckUpWhite = whiteLeft;                 //used for quick revert
    bckUpWheat = wheatLeft;                 //quick revet back to changes
    //find sticks remaining from last box
    whiteLeft = whiteLeft - finalWhite;
    if(whiteLeft < 0)
        whiteLeft = stcksPerBox + whiteLeft;
    wheatLeft = wheatLeft - finalWheat;
    if(wheatLeft < 0)
        wheatLeft = stcksPerBox + wheatLeft;

    //display data and show window
    fin->res(this);
    fin->show();
}

int breadData::round(int num)
{
    if(RND_UP)                          //if always round up
        return num + (rndSticksTo - (num % rndSticksTo));
    if(num % rndSticksTo < 2)
        return num - num % rndSticksTo;
    else
        return num + (rndSticksTo - (num % rndSticksTo));
}

void breadData::revertSticks()
{
    whiteLeft = bckUpWhite;
    wheatLeft = bckUpWheat;
}

bool breadData::getRND_UP()
{
    return RND_UP;
}
int breadData::getStcksPerBox()
{
    return stcksPerBox;
}
int breadData::getRndSticksTo()
{
    return rndSticksTo;
}
double breadData::getBreadCost()
{
    return breadCost;
}

int breadData::getEstSales(DAY d)
{
    switch(d) {
        case MON:
            return dailySales.at(1);
        case TUES:
            return dailySales.at(2);
        case WEDS:
            return dailySales.at(3);
        case THURS:
            return dailySales.at(4);
        case FRI:
            return dailySales.at(5);
        case SAT:
            return dailySales.at(6);
        case SUN:
            return dailySales.at(0);
        default:
            return -1;
    }
}

void breadData::setRND_UP(bool b)
{
    RND_UP = b;
}

void breadData::setStcksPerBox(int x)
{
    stcksPerBox = x;
}

void breadData::setRndSticksTo(int x)
{
    rndSticksTo = x;
}

void breadData::setWhiteLeft(int x)
{
    whiteLeft = x;
}

void breadData::setWheatLeft(int x)
{
    wheatLeft = x;
}

void breadData::setBreadCost(double y)
{
    breadCost = y;
}

void breadData::setDailySales(std::vector<unsigned int> cpy)
{
    for(int i=0; i<(int)dailySales.size();i++) {        //loop for each day
        dailySales.at(i) = cpy.at(i);
    }
}

