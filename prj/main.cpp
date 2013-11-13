#include "mainwindow.h"
#include "breaddata.h"
#include <string>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);         //internal app
    MainWindow w;                       //main window
    breadData dat("format.dat");        //create bread object
    if(!w._link(&dat))                  //link main window with bread data
        return 1;
    else
        w.show();                       //show main window
    return a.exec();                    //execute loop
}
