#include "resultwnd.h"
#include "breaddata.h"
#include "ui_resultwnd.h"
#include <sstream>

resultWnd::resultWnd(QWidget *parent, breadData *dat) :
    QGroupBox(parent),
    ui(new Ui::resultWnd)
{
    std::stringstream ss;
    ss << dat->getFinalWhite() << " sticks of white";
    ui->setupUi(this);
    ui->fWhite->setText(QMainWindow::tr(ss.str().c_str()));
    ss.str("");
    ss << dat->getFinalWheat() << " sticks of wheat";
    ui->fWheat->setText(QMainWindow::tr(ss.str().c_str()));
    ss.str("");
    ss << "Wheat: " << dat->getWheatLeft();
    ui->lWheat->setText(QMainWindow::tr(ss.str().c_str()));
    ss.str("");
    ss << "White: " << dat->getWhiteLeft();
    ui->lWhite->setText(QMainWindow::tr(ss.str().c_str()));

}

resultWnd::~resultWnd()
{
    delete ui;
}

void resultWnd::on_commandLinkButton_clicked()
{
    close();
}
