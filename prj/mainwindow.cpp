#include "mainwindow.h"
#include "settings.h"
#include "breaddata.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "log.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    internalState(NONE),
    s(NULL),
    lg(NULL)
{
    lg = new Log(this);
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
    if(s != NULL)
        delete s;
    if(ui != NULL)
        delete ui;
    if(lg != NULL)
        delete lg;
}

//link the main window with a bread object to be used for calculations and auditing
bool MainWindow::_link(breadData *obj)
{

    if(obj == NULL) {                                   //make sure user passed in valid object file
        QMessageBox::critical(this,tr("Error_link()"),tr("breadData passed is NULL"));
        return false;
    }

    dit = obj;                                          //object is not NULL, so set internal data
    dit->_brdLink(this,ui);                             //link bread object with this window
    if(!dit->readData()){
        QMessageBox::information(this,tr("Skipping"),tr("No file was created...Exiting..."));
        return false;
    }
    s = new Settings(this,dit);                         //main window and breadData object for displaying
    return true;
}

//determines if a catering order exists
void MainWindow::on_comboBox_activated(const QString &arg1)
{

    if(arg1 == tr("Mixed(FEET)")) {                               //if the catering order is mixed bread, only one input source is needed
        internalState = MIXED;
        ui->whiteCL->setText(tr("FEET of Bread:"));         //set the text to account for only one set of input
        ui->whiteCL->show();
        ui->whiteCIN->show();
        if(!ui->wheatCL->isHidden()) {                      //make sure second box is hidden
            ui->wheatCL->hide();
        }
        if(!ui->wheatCIN->isHidden()) {
            ui->wheatCIN->hide();
        }
    }
    //custom amount of sticks entered
    if(arg1 == tr("Custom(STICKS)")) {
        internalState = CUSTOM;
        ui->whiteCL->setText(tr("Catering White:"));        //show both hidden input sources
        ui->wheatCL->show();
        ui->whiteCL->show();
        ui->wheatCIN->show();
        ui->whiteCIN->show();
    }
    //rehide labels to make sure, internal state is none
    if(arg1 == tr("None")) {
        ui->whiteCL->hide();
        ui->wheatCL->hide();
        ui->whiteCIN->hide();
        ui->wheatCIN->hide();
        internalState = NONE;
    }
}

void MainWindow::on_showBread_clicked()
{
    if(!dit->readData()){
        QApplication::quit();
    } else {
        if(dit->checkNewWeek()) {               //make sure user knows that tommorow is a new week!
            dit->gatherInput(internalState);    //read user entered input
            dit->calculateBread();              //find results
            dit->writeData();                   //write any new data to file
            dit->writeLog();
        } else
            QMessageBox::information(this,tr("Skipped"),tr("Nothing was done..."));
    }

}


void MainWindow::on_actionEdit_values_triggered()
{

    s->showData();      //display data to settings window
    s->show();          //show window
}


void MainWindow::on_actionContact_me_about_issues_triggered()
{
    //create message box to display contact info
    QMessageBox message;
    message.setWindowTitle(tr("Feedback/issues"));
    message.setTextFormat(Qt::RichText);
    message.setText("Please contact me at <a href=\"mailto:brdcount.help@gmail.com\">brdcount.help@gmail.com</a>");
    message.setStandardButtons(QMessageBox::Ok);
    message.exec();
}

void  MainWindow::on_actionRevert_stcks_Left_to_last_value_triggered()
{
    std::stringstream ss;
    ss << "Revert (" << dit->getWhiteLeft() << "/" << dit->getWheatLeft() << ") sticks left to"
       << " (" << dit->getBackUpWhite() << "/" << dit->getBackUpWheat() << ") sticks left?: (WHITE/WHEAT)";
    //ask user if he/she is sure they want to revert, then move forward with revert if so
    if(QMessageBox::information(this,tr("Revert?"),tr(ss.str().c_str()),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
        dit->revertSticks();
    else
        return;

}

void MainWindow::on_actionHelp_me_please_triggered()
{
    std::stringstream s;
    s <<
         "Setup\n\nThe only prerequisites are the daily estimates for the week"
      << " and the amount of bread left in the white/wheat box before pulling. You can access these values by going to Vars->Edit Values"
      << " . Modify the values to fit your bread pull and hit OK(not hitting ok will cancel any changes).\n\n" <<
         "Using\n\nCount the number of baked white and wheat sticks you have on hand. Once counted check"
      << " for any catering orders due the next day, if an order asks to mix the bread select the 'Mixed' tab and enter how many feet of sandwich were ordered. If the catering"
      << " order specifies an uneven amount of white and wheat, choose 'Custom' and enter the amount of sticks needed. Afterwards hit show and the amount of bread needed for the"
      << " pull along with the remaining white/wheat will be displayed.";
    QMessageBox::information(this,tr("HowTo"),tr(s.str().c_str()));
}

void MainWindow::on_actionLog_triggered()
{
    dit->writeLog(RESET_HARD);
}

void MainWindow::on_actionData_triggered()
{
    if(QMessageBox::question(this,tr("Data Reset"),tr("Reseting the data will require the program to exit. Continue?"),QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        if( remove("format.dat") != 0) {
            QMessageBox::information(this, tr("Error_Reset()"), tr("Error deleting data file..."));
        }
        QApplication::quit();

    }
}

void MainWindow::on_actionShow_Log_triggered()
{
    lg->show();
    lg->showLog();
}
