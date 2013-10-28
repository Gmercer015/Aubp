#include "mainwindow.h"
#include "breaddata.h"
#include <string>
#include <QApplication>\

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    breadData dat("audit.dat");
    //link main window with bread data
    w._link(&dat);
    //show main window
    w.show();
    //execute loop
    return a.exec();
}
