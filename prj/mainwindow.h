#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_showBread_clicked();

private:
    Ui::MainWindow *ui;
    //determines if caterting order is present
    unsigned short internalState;
};

#endif // MAINWINDOW_H
