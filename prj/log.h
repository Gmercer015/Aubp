#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include "breaddata.h"

namespace Ui {
class Log;
}

class Log : public QDialog
{
    Q_OBJECT

public:
    explicit Log(QWidget *parent = 0, breadData *db = NULL);
    ~Log();

    void showLog();

private:
    Ui::Log *ui;
    breadData *dit;
};

#endif // LOG_H
