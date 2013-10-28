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
        QMessageBox::critical(mainWnd,QMainWindow::tr("Error"), QMainWindow::tr("Could not open file"));
        return false;
    }
    return true;
}

void breadData::gatherInput(int IS)
{

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
    }
}


