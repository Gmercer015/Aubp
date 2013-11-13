#include "log.h"
#include "ui_log.h"
#include "breaddata.h"
#include <sstream>
#include <string>

Log::Log(QWidget *parent, breadData *db) :
    QDialog(parent),
    ui(new Ui::Log)
{
    ui->setupUi(this);
    dit = db;
}

Log::~Log()
{
    delete ui;
}

void Log::showLog()
{
    std::stringstream ss;
    dit->getLog(ss);
    if(ss.str() == "")
        ss << "No Log Information";
    ui->LogDisplay->setText(tr(ss.str().c_str()));
}
