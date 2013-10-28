#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    internalState(0)
{
    ui->setupUi(this);
    //hide catering buttons until user selections catering option
    ui->wheatCL->hide();
    ui->whiteCL->hide();
    ui->wheatCIN->hide();
    ui->whiteCIN->hide();
}


MainWindow::~MainWindow()
{
    delete ui;
}

//link the main window with a bread object to be used for calculations and auditing
void MainWindow::_link(breadData *obj)
{
    //make sure user passed in valid object file
    if(obj == NULL) {
        QMessageBox::critical(this,tr("Error"),tr("breadData passed is NULL"));
        return;
    }
    //object is not NULL, so set internal data
    dit = obj;
    //link bread object with this window
    dit->_brdLink(this,ui);
}

//determines if a catering order exists
void MainWindow::on_comboBox_activated(const QString &arg1)
{
    //if the catering order is mixed bread, only one input source is needed
    if(arg1 == tr("Mixed")) {
        internalState = 1;
        //set the text to account for only one set of input
        ui->whiteCL->setText(tr("Feet of Bread:"));
        ui->whiteCL->show();
        ui->whiteCIN->show();
        //make sure second box is hidden
        if(!ui->wheatCL->isHidden()) {
            ui->wheatCL->hide();
        }
        if(!ui->wheatCIN->isHidden()) {
            ui->wheatCIN->hide();
        }
    }
    //with custom catering two input sources are needed
    if(arg1 == tr("Custom")) {
        internalState = 2;
        //show both hidden input sources
        ui->whiteCL->setText(tr("Catering White:"));
        ui->wheatCL->show();
        ui->whiteCL->show();
        ui->wheatCIN->show();
        ui->whiteCIN->show();
    }
    //if user switches back to 'none' then internal state must be false
    if(arg1 == tr("None")) {
        internalState = 0;
    }
}

//show button is clicked
void MainWindow::on_showBread_clicked()
{
    dit->gatherInput(internalState);
}


void MainWindow::on_actionNo_Tools_yet_triggered()
{

}
