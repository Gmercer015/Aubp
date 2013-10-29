#ifndef BREADDATA_H
#define BREADDATA_H

#include <vector>
#include <string>
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QMainWindow>

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
    void gatherInput(int);

    //calculate bread needed using given values
    void calculateBread();

    void writeData();

    //for quick tools
    void revertSticks();

    //access functions
    unsigned int getFinalWhite(){return finalWhite;}
    unsigned int getFinalWheat(){return finalWheat;}
    int getWhiteLeft(){return whiteLeft;}
    int getWheatLeft(){return wheatLeft;}
    bool getRND_UP();
    int getStcksPerBox();
    int getRndSticksTo();
    double getBreadCost();
    std::vector<unsigned int>::iterator getPointerSales();
    //set functions
    void setRND_UP(bool);
    void setStcksPerBox(int);
    void setRndSticksTo(int);
    void setWhiteLeft(int);
    void setWheatLeft(int);
    void setBreadCost(double);
    void setDailySales(unsigned int*);


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
    int bckUpWhite;                                 //quick revert to last val
    int bckUpWheat;                                 //quick revert to last val
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
