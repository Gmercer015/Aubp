#include "settings.h"
#include "breaddata.h"
#include "ui_settings.h"
#include <sstream>

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
