#ifndef BREADDATA_H
#define BREADDATA_H

#include <vector>
#include <string>
#include <QtWidgets>
#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultwnd.h"

class MainWindow;
class resultWnd;

class breadData
{
public:
    breadData(std::string);
    ~breadData();
    //read in data file that provides all information
    bool readData();

    //access functions
    unsigned int getFinalWhite(){return finalWhite;}
    unsigned int getFinalWheat(){return finalWheat;}
    int getWhiteLeft(){return whiteLeft;}
    int getWheatLeft(){return wheatLeft;}

    //link with object that grabs bread
    void _brdLink(QMainWindow *linker=NULL, Ui::MainWindow *ui=NULL);

    //get input from boxes on window
    void gatherInput(int);

    //calculate bread needed using given values
    void calculateBread();

    void writeData();

    //set functions
    void setWhite(unsigned int x){ whiteSticks = x;}
    void setWheat(unsigned int x){ wheatSticks = x;}

protected:
    int whiteSticks;                                //user input
    int wheatSticks;                                //user input

    unsigned int finalWhite;                        //final sticks needed
    unsigned int finalWheat;

    bool RND_UP;                                    //default = FALSE
    int stcksPerBox;                                //default = 30
    int rndSticksTo;                                //default = 4
    int whiteLeft;                                  //default = 30
    int wheatLeft;                                  //default = 30
    double breadCost;                               //default = 18.5
    //includes for every day of the week
    std::vector<unsigned int> dailySales;           //sales throughout the week
private:
    int round(int);                                 //round func for algorithm
    Ui::MainWindow *usI;                            //main window UI
    QWidget *mainWnd;                               //for displaying errors
    resultWnd *fin;
    std::string fileName;                           //name of input file
};

#endif // BREADDATA_H
