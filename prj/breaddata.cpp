#include "breaddata.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QMainWindow>
#include <QtWidgets>
#include <sstream>
#include <fstream>

breadData::breadData(std::string fileIn)
{
    fileName = fileIn;
    RND_UP = false;
}

//grabs window object in order to display error messages/data
void breadData::_brdLink(QMainWindow *linker, Ui::MainWindow *ui)
{
    //set the internal window to display data to mainWnd
    mainWnd = linker;
    usI = ui;
}

//read in data file that provides all information
bool breadData::readData()
{
    //temp string to grab file data
    std::string readTMP;
    //open file to read
    std::ifstream inFile(fileName.c_str());
    //if the file cannot be read, critical message and return false
    if(!inFile.is_open()) {
        QMessageBox::critical(mainWnd,QMainWindow::tr("Error_readData()"), QMainWindow::tr("Could not open file"));
        return false;
    }
    std::stringstream info;
    while(inFile >> readTMP) {
        //ROUNDING BOOL READ IN
        if(readTMP == "BOOLRND"){
            inFile >> readTMP;
            if(readTMP == "TRUE"){
                RND_UP = true;
                info  << "true ";
            }else{
                RND_UP = false;
                info << "false ";}
        }
        if(readTMP == "DAILYSALES"){
            for(int i = 0; i < 5; i++){
                int projectedSales;
                inFile >> projectedSales;
                dailySales.push_back(projectedSales);
                info << projectedSales << " ";
            }
        }
    }
    //debug infomation to show that the file is reading correctly
    QMessageBox::information(mainWnd,QMainWindow::tr("info"),QMainWindow::tr(info.str().c_str()));
    return true;
}

void breadData::gatherInput(int IS)
{
    //wrap if statement to make sure these are set. IF NOT THE PROGRAM WILL FUCKING EXPLODE
    if(usI != NULL && mainWnd != NULL){
    std::stringstream ss;
    switch(IS) {
        //no cater
        case 0:
            //stick count for use with algorithm
            whiteSticks = usI->whiteIN->value();
            wheatSticks = usI->wheatIN->value();
            ss << whiteSticks << "," << wheatSticks;
            usI->Debug->setText(QMainWindow::tr(ss.str().c_str()));
        break;
        //mixed bread 1 IN
        case 1:
            whiteSticks = usI->whiteIN->value() + (usI->whiteCIN->value() / 2) / 2;
            wheatSticks = usI->wheatIN->value() + (usI->whiteCIN->value() / 2) / 2;
            ss << whiteSticks << "," << wheatSticks;
            usI->Debug->setText(QMainWindow::tr(ss.str().c_str()));
        break;
        //custom 2 IN
        case 2:
            whiteSticks = usI->whiteIN->value() + usI->whiteCIN->value();
            wheatSticks = usI->wheatIN->value() + usI->wheatCIN->value();
            ss << whiteSticks << "," << wheatSticks;
            usI->Debug->setText(QMainWindow::tr(ss.str().c_str()));
        break;
    }}else
        QMessageBox::critical(mainWnd,QMainWindow::tr("Error_gatherInput()"),QMainWindow::tr("BreadOBJ not is not linked FATAL"));
}


