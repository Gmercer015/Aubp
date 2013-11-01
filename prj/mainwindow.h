#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class breadData;
class Settings;

//for internal state
enum STATE{
    NONE=0,
    MIXED=1,
    CUSTOM=2
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void _link(breadData *obj);\

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_showBread_clicked();

    void on_actionContact_me_about_issues_triggered();

    void on_actionEdit_values_triggered();

    void on_actionRevert_stcks_Left_to_last_value_triggered();

private:
    Ui::MainWindow *ui;
    //determines if caterting order is present
    STATE internalState;
    //bread data for program!
    Settings *s;
    breadData *dit;
};

#endif // MAINWINDOW_H
