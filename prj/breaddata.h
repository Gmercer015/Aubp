#ifndef BREADDATA_H
#define BREADDATA_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QtWidgets>
#include <QMainWindow>

enum DAY{
    SUN=0,
    MON=1,
    TUES=2,
    WEDS=3,
    THURS=4,
    FRI=5,
    SAT=6
};

const int WEEK_COUNT = 7;
const int RESET_HARD = -1;

class resultWnd;

class breadData
{
public:
    breadData(std::string);
    breadData(){}
    ~breadData();
    //read in data file that provides all information
    bool readData();

    //link with object that grabs bread
    void _brdLink(QMainWindow *linker=NULL, Ui::MainWindow *ui=NULL);

    //get input from boxes on window
    void gatherInput(STATE);

    //calculate bread needed using given values
    void calculateBread();

    //check if new week and notify user
    bool checkNewWeek();

    //write data to file
    void writeData();
    void writeLog(int key=0);

    //for quick tools
    void revertSticks();

    //access functions
    unsigned int getFinalWhite(){return finalWhite;}
    unsigned int getFinalWheat(){return finalWheat;}
    int getWhiteLeft(){return whiteLeft;}
    int getWheatLeft(){return wheatLeft;}
    int getBackUpWhite() {return bckUpWhite;}
    int getBackUpWheat() {return bckUpWheat;}
    bool getRND_UP();
    int getStcksPerBox();
    int getRndSticksTo();
    double getBreadCost();
    void getLog(std::stringstream& ss);
    int getEstSales(DAY);
    //set functions
    void setRND_UP(bool);
    void setStcksPerBox(int);
    void setRndSticksTo(int);
    void setWhiteLeft(int);
    void setWheatLeft(int);
    void setBreadCost(double);
    void setDailySales(std::vector<unsigned int>);


protected:
    int whiteSticks;                                //user input
    int wheatSticks;                                //user input

    int finalWhite;                                 //final sticks needed
    int finalWheat;

    unsigned long statWhitePulled;                  //total white pulled(log)
    unsigned long statWheatPulled;                  //total wheat pulled(log)

    bool RND_UP;                                    //default = FALSE
    int stcksPerBox;                                //default = 30
    int rndSticksTo;                                //default = 4
    int whiteLeft;                                  //default = 30
    int wheatLeft;                                  //default = 30
    int bckUpWhite;                                 //quick revert to last val
    int bckUpWheat;                                 //quick revert to last val
    double breadCost;                               //default = 18.5
    //includes for every day of the week
    std::vector<unsigned int> dailySales;           //default = 1000
private slots:
    void on_queryUpdate_triggered();

private:
    int round(int);                                 //round func for algorithm
    Ui::MainWindow *usI;                            //main window UI
    QWidget *mainWnd;                               //for displaying errors
    resultWnd *fin;
    std::string fileName;                           //name of input file
};

#endif // BREADDATA_H
