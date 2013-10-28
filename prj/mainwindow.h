#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "breaddata.h"

class breadData;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void _link(breadData *obj);

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_showBread_clicked();

    void on_actionNo_Tools_yet_triggered();

    void on_actionContact_me_about_issues_triggered();

private:
    Ui::MainWindow *ui;
    //determines if caterting order is present
    unsigned short internalState;
    //bread data for program!
    breadData *dit;
};

#endif // MAINWINDOW_H
