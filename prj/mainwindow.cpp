#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    internalState(0),
    whiteSticks(0),
    wheatSticks(0)
{
    ui->setupUi(this);
    ui->wheatCL->hide();
    ui->whiteCL->hide();
    ui->wheatCIN->hide();
    ui->whiteCIN->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    std::stringstream ss;
    switch(internalState) {
        //no cater
        case 0:
            //stick count for use with algorithm
            whiteSticks = ui->whiteIN->value();
            wheatSticks = ui->wheatIN->value();
            ss << whiteSticks << "," << wheatSticks;
            ui->Debug->setText(tr(ss.str().c_str()));
        break;
        //mixed bread 1 IN
        case 1:
            whiteSticks = ui->whiteIN->value() + (ui->whiteCIN->value() / 2) / 2;
            wheatSticks = ui->wheatIN->value() + (ui->whiteCIN->value() / 2) / 2;
            ss << whiteSticks << "," << wheatSticks;
            ui->Debug->setText(tr(ss.str().c_str()));
        break;
        //custom 2 IN
        case 2:
            whiteSticks = ui->whiteIN->value() + ui->whiteCIN->value();
            wheatSticks = ui->wheatIN->value() + ui->wheatCIN->value();
            ss << whiteSticks << "," << wheatSticks;
            ui->Debug->setText(tr(ss.str().c_str()));
        break;
    }

}
