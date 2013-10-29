#include "breaddata.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    breadCost(18.5)
{
    fileName = fileIn;
}

breadData::~breadData()
{
    delete fin;
}

//grabs window object in order to display error messages/data
void breadData::_brdLink(QMainWindow *linker, Ui::MainWindow *ui)
{
    //set the internal window to display data to mainWnd
    mainWnd = linker;
    usI = ui;
}

void breadData::writeData()
{
    std::ofstream writeOut;
    writeOut.open("format.dat");
    if(!writeOut.is_open()){
        QMessageBox::critical(mainWnd,QMainWindow::tr("Error_writeData()"),QMainWindow::tr("Could not open file to write"));
        return;
    }
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
    writeOut << "\nBRDCONST\n" << breadCost << "\n";
    writeOut.close();
}

//read in data file that provides all information
bool breadData::readData()
{
    std::string readTMP;                        //temp string to grab file data
    std::ifstream inFile(fileName.c_str());     //open file to read
    //if the file cannot be read, critical message and return false
    if(!inFile.is_open()) {
        QMessageBox::critical(mainWnd,QMainWindow::tr("Error_readData()"), QMainWindow::tr("Could not open file"));
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
                dailySales.push_back(projectedSales);
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
        if(readTMP == "BRDCONST"){
            inFile >> breadCost;
        }
    }
    inFile.close();
    return true;
}

void breadData::gatherInput(int IS)
{
    //wrap if statement to make sure these are set. IF NOT THE PROGRAM WILL FUCKING EXPLODE
    if(usI != NULL && mainWnd != NULL){
    switch(IS) {
        //no cater
        case 0:
            //stick count for use with algorithm
            whiteSticks = usI->whiteIN->value();
            wheatSticks = usI->wheatIN->value();
        break;
        //mixed bread 1 IN
        case 1:
            whiteSticks = usI->whiteIN->value() - ceil(usI->whiteCIN->value() / 4.0);
            wheatSticks = usI->wheatIN->value() - ceil(usI->whiteCIN->value() / 4.0);
        break;
        //custom 2 IN
        case 2:
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

    //find sticks remaining from last box
    whiteLeft = whiteLeft - finalWhite;
    if(whiteLeft < 0)
        whiteLeft = 30 + whiteLeft;
    wheatLeft = wheatLeft - finalWheat;
    if(wheatLeft < 0)
        wheatLeft = 30 + wheatLeft;

    //show results in dialog box
    fin = new resultWnd(mainWnd, this);
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
