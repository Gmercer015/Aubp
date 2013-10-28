#ifndef BREADDATA_H
#define BREADDATA_H

#include <vector>
#include <string>
#include <QtWidgets>
#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class MainWindow;

class breadData
{
public:
    breadData(std::string);
    //read in data file that provides all information
    bool readData();

    //access functions
    unsigned int getWhite(){return whiteSticks;}
    unsigned int getWheat(){return wheatSticks;}

    //link with object that grabs bread
    void _brdLink(QMainWindow *linker=NULL, Ui::MainWindow *ui=NULL);

    //get input from boxes on window
    void gatherInput(int);

    //set functions
    void setWhite(unsigned int x){ whiteSticks = x;}
    void setWheat(unsigned int x){ wheatSticks = x;}

private:
    Ui::MainWindow *usI;
    QWidget *mainWnd;
    //daily sales of the week to be read in from data file
    std::vector<std::string> dailySales;
    //filename
    std::string fileName;
    //stick amount
    unsigned int whiteSticks;
    unsigned int wheatSticks;

};

#endif // BREADDATA_H
