#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "breaddata.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0,breadData *cp=0);
    Settings();
    ~Settings();
    void showData();
    void writeBackToFileUpdate();
private slots:
    void on_WriteCance_accepted();

private:

    Ui::Settings *ui;
    breadData *cpy;
};

#endif // SETTINGS_H
