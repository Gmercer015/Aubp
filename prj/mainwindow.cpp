#include "mainwindow.h"
#include "settings.h"
#include "breaddata.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    internalState(0)
{
    setFixedHeight(273);
    setFixedWidth(364);
    ui->setupUi(this);
    //hide catering buttons until user selections catering option
    ui->wheatCL->hide();
    ui->whiteCL->hide();
    ui->wheatCIN->hide();
    ui->whiteCIN->hide();
}


MainWindow::~MainWindow()
{
    //free memory
    delete s;
    delete ui;
}

//link the main window with a bread object to be used for calculations and auditing
void MainWindow::_link(breadData *obj)
{
    //make sure user passed in valid object file
    if(obj == NULL) {
        QMessageBox::critical(this,tr("Error_link()"),tr("breadData passed is NULL"));
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
        ui->whiteCL->hide();
        ui->wheatCL->hide();
        ui->whiteCIN->hide();
        ui->wheatCIN->hide();
        internalState = 0;
    }
}

//show button is clicked
void MainWindow::on_showBread_clicked()
{
    dit->readData();                    //read data from file
    dit->gatherInput(internalState);    //read user entered input
    dit->calculateBread();              //find results
    dit->writeData();                   //write any new data to file
}


void MainWindow::on_actionEdit_values_triggered()
{
    s = new Settings(this);
    s->show();
}


void MainWindow::on_actionContact_me_about_issues_triggered()
{
    QMessageBox message;
    message.setWindowTitle(tr("Feedback/issues"));
    message.setTextFormat(Qt::RichText);
    message.setText("<a href=\"mailto:brdcount.help@gmail.com\">brdcount.help@gmail.com</a>\nplease expect a couple days before a response, I'll try my best to answer your question/issue.");
    message.setStandardButtons(QMessageBox::Ok);
    message.exec();
}

void  MainWindow::on_actionRevert_stcks_Left_to_last_value_triggered()
{
    if(QMessageBox::information(this,tr("Revert?"),tr("revert sticks to prev recorded?"),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
        dit->revertSticks();
    else
        return;

}
