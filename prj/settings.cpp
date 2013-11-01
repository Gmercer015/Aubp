#include "settings.h"
#include "breaddata.h"
#include "ui_settings.h"
#include <QMainWindow>
#include <sstream>
#include <vector>

Settings::Settings(QWidget *parent,breadData *cp) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    cpy = cp;
    ui->setupUi(this);
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
    cpy->writeData();
    cpy->readData();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_WriteCance_accepted()
{
    writeBackToFileUpdate();
}
