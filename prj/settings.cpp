#include "settings.h"
#include "breaddata.h"
#include "ui_settings.h"
#include <QMainWindow>
#include <sstream>
#include <vector>
#include <cstdlib>

Settings::Settings(QWidget *parent,breadData *cp) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    cpy = cp;
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}


void Settings::showData()
{
    //set default values in label
    std::string bbl = (cpy->getRND_UP() == false ? "FALSE" : "TRUE");
    std::stringstream ss;
    ui->RNDUPIN->setCurrentText( QMainWindow::tr(bbl.c_str()) );
    ui->StcksPerBoxIN->setValue( cpy->getStcksPerBox() );
    ui->RndBreadToIN->setValue( cpy->getRndSticksTo() );
    ui->WhiteLeftIN->setValue( cpy->getWhiteLeft() );
    ui->WheatLeftIN->setValue( cpy->getWheatLeft() );
    ui->BreadCostIN->setValue( cpy->getBreadCost() );
    //using a string stream to display values into text labels
    ss << cpy->getEstSales(MON);
    ui->MonIN->setText( QMainWindow::tr(ss.str().c_str()) );
    ss.str(""); ss.clear(); ss << cpy->getEstSales(TUES);
    ui->TuesIN->setText( QMainWindow::tr(ss.str().c_str()) );
    ss.str(""); ss.clear(); ss << cpy->getEstSales(WEDS);
    ui->WedsIN->setText( QMainWindow::tr(ss.str().c_str()) );
    ss.str(""); ss.clear(); ss << cpy->getEstSales(THURS);
    ui->ThursIN->setText( QMainWindow::tr(ss.str().c_str()) );
    ss.str(""); ss.clear(); ss << cpy->getEstSales(FRI);
    ui->FriIN->setText( QMainWindow::tr(ss.str().c_str()) );
    ss.str(""); ss.clear(); ss << cpy->getEstSales(SAT);
    ui->SatIN->setText( QMainWindow::tr(ss.str().c_str()) );
    ss.str(""); ss.clear(); ss << cpy->getEstSales(SUN);
    ui->SunIN->setText( QMainWindow::tr(ss.str().c_str()) );
}

void Settings::writeBackToFileUpdate()
{
    getSetData();
    cpy->writeData();
    cpy->readData();
}

void Settings::getSetData()
{
    std::stringstream ss;
    int dontaskagain = cpy->getStcksPerBox();               //for protected var
    //STICKS PER BOX
    int tmp = ui->StcksPerBoxIN->value();
    //might be accidental input, make sure user wants these values
    if( (tmp != 30) && (tmp != dontaskagain) ) {
        std::stringstream ss;
        ss << "You are changing a protected variable, are you sure your stores boxes contain "
           << tmp << " sticks of bread per box?";
        if(QMessageBox::question(this,
                                QMainWindow::tr("Box count change"),
                                QMainWindow::tr(ss.str().c_str()),
                                QMessageBox::Yes,
                                QMessageBox::No) == QMessageBox::Yes)
            cpy->setStcksPerBox(tmp);

    } else
        cpy->setStcksPerBox(tmp);

    //ROUND BREAD TO NEAREST
    tmp = ui->RndBreadToIN->value();
    if(tmp < 2)
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr("ROUND BREAD TO cannot be less than 2... Skipping"));
    else
        cpy->setRndSticksTo(tmp);

    //WHITE LEFT IN BOX
    tmp = ui->WhiteLeftIN->value();
    if(tmp < 0 || tmp > cpy->getStcksPerBox()) {
        ss.str(""); ss.clear();
        ss << "WHITE LEFT cannot be less than zero or more than " << cpy->getStcksPerBox() << "... Skipping";
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr(ss.str().c_str()));
    } else
        cpy->setWhiteLeft(tmp);

    //WHEAT LEFT IN BOX
    tmp = ui->WheatLeftIN->value();
    if(tmp < 0 || tmp > cpy->getStcksPerBox()) {
        ss.str(""); ss.clear();
        ss << "WHEAT LEFT cannot be less than zero or more than " << cpy->getStcksPerBox() << "... Skipping";
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr(ss.str().c_str()));
    } else
        cpy->setWheatLeft(tmp);

    //BREAD COST
    double tmpb = ui->BreadCostIN->value();
    if(tmpb < 1)
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr("BREAD COST cannot be less than 1... Skipping"));
    else
        cpy->setBreadCost(tmpb);

    //DAILY SALES TALKING ABOUT FUCKING INEFFICIENT
    std::vector<unsigned int>tmpSales;
    for(int i =0; i < WEEK_COUNT; i++)
        tmpSales.push_back(1000);
    //monday
    tmp = atoi(ui->MonIN->text().toStdString().c_str());
    if(tmp < 0){
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr("Monday sales cannot fall below 0... Skipping"));
        tmpSales.push_back(cpy->getEstSales(MON));
    }else
        tmpSales.at(MON) = tmp;

    //tuesday
    tmp = atoi(ui->TuesIN->text().toStdString().c_str());
    if(tmp < 0){
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr("Tuesday sales cannot fall below 0... Skipping"));
        tmpSales.push_back(cpy->getEstSales(TUES));
    }else
        tmpSales.at(TUES) = tmp;

    //wednesday
    tmp = atoi(ui->WedsIN->text().toStdString().c_str());
    if(tmp < 0){
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr("Wednesday sales cannot fall below 0... Skipping"));
        tmpSales.push_back(cpy->getEstSales(WEDS));
    }else
        tmpSales.at(WEDS) = tmp;

    //thursday
    tmp = atoi(ui->ThursIN->text().toStdString().c_str());
    if(tmp < 0){
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr("Thursday sales cannot fall below 0... Skipping"));
        tmpSales.push_back(cpy->getEstSales(THURS));
    }else
        tmpSales.at(THURS) = tmp;

    //friday
    tmp = atoi(ui->FriIN->text().toStdString().c_str());
    if(tmp < 0){
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr("Friday sales cannot fall below 0... Skipping"));
        tmpSales.push_back(cpy->getEstSales(FRI));
    }else
        tmpSales.at(FRI) = tmp;

    //saturday
    tmp = atoi(ui->SatIN->text().toStdString().c_str());
    if(tmp < 0){
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr("Saturday sales cannot fall below 0... Skipping"));
        tmpSales.push_back(cpy->getEstSales(SAT));
    }else
        tmpSales.at(SAT) = tmp;

    //sunday
    tmp = atoi(ui->TuesIN->text().toStdString().c_str());
    if(tmp < 0){
        QMessageBox::critical(this,QMainWindow::tr("Error"),QMainWindow::tr("Sunday sales cannot fall below 0... Skipping"));
        tmpSales.push_back(cpy->getEstSales(SUN));
    }else
        tmpSales.at(SUN) = tmp;

    cpy->setDailySales(tmpSales);
}

void Settings::on_WriteCance_accepted()
{
    writeBackToFileUpdate();
}

void Settings::on_RNDUPIN_activated(const QString &arg1)
{
    if(arg1 == "FALSE")
        cpy->setRND_UP(false);
    else
        cpy->setRND_UP(true);
}
