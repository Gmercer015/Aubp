/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEnviromentVars;
    QAction *actionModify;
    QAction *actionNew_ENVVAR_dir;
    QAction *actionRound;
    QAction *actionHelp_me_please;
    QAction *actionNo_Tools_yet;
    QWidget *centralwidget;
    QPushButton *showBread;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *whiteL;
    QSpinBox *whiteIN;
    QLabel *wheatL;
    QSpinBox *wheatIN;
    QLabel *catPrompt;
    QComboBox *comboBox;
    QLabel *whiteCL;
    QSpinBox *whiteCIN;
    QLabel *wheatCL;
    QSpinBox *wheatCIN;
    QLabel *Debug;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(358, 241);
        actionEnviromentVars = new QAction(MainWindow);
        actionEnviromentVars->setObjectName(QStringLiteral("actionEnviromentVars"));
        actionModify = new QAction(MainWindow);
        actionModify->setObjectName(QStringLiteral("actionModify"));
        actionNew_ENVVAR_dir = new QAction(MainWindow);
        actionNew_ENVVAR_dir->setObjectName(QStringLiteral("actionNew_ENVVAR_dir"));
        actionRound = new QAction(MainWindow);
        actionRound->setObjectName(QStringLiteral("actionRound"));
        actionHelp_me_please = new QAction(MainWindow);
        actionHelp_me_please->setObjectName(QStringLiteral("actionHelp_me_please"));
        actionNo_Tools_yet = new QAction(MainWindow);
        actionNo_Tools_yet->setObjectName(QStringLiteral("actionNo_Tools_yet"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        showBread = new QPushButton(centralwidget);
        showBread->setObjectName(QStringLiteral("showBread"));
        showBread->setGeometry(QRect(120, 160, 81, 31));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 21, 341, 131));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        whiteL = new QLabel(layoutWidget);
        whiteL->setObjectName(QStringLiteral("whiteL"));

        formLayout->setWidget(0, QFormLayout::LabelRole, whiteL);

        whiteIN = new QSpinBox(layoutWidget);
        whiteIN->setObjectName(QStringLiteral("whiteIN"));

        formLayout->setWidget(0, QFormLayout::FieldRole, whiteIN);

        wheatL = new QLabel(layoutWidget);
        wheatL->setObjectName(QStringLiteral("wheatL"));

        formLayout->setWidget(1, QFormLayout::LabelRole, wheatL);

        wheatIN = new QSpinBox(layoutWidget);
        wheatIN->setObjectName(QStringLiteral("wheatIN"));

        formLayout->setWidget(1, QFormLayout::FieldRole, wheatIN);

        catPrompt = new QLabel(layoutWidget);
        catPrompt->setObjectName(QStringLiteral("catPrompt"));

        formLayout->setWidget(2, QFormLayout::LabelRole, catPrompt);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, comboBox);

        whiteCL = new QLabel(layoutWidget);
        whiteCL->setObjectName(QStringLiteral("whiteCL"));
        whiteCL->setEnabled(true);

        formLayout->setWidget(3, QFormLayout::LabelRole, whiteCL);

        whiteCIN = new QSpinBox(layoutWidget);
        whiteCIN->setObjectName(QStringLiteral("whiteCIN"));
        whiteCIN->setEnabled(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, whiteCIN);

        wheatCL = new QLabel(layoutWidget);
        wheatCL->setObjectName(QStringLiteral("wheatCL"));
        wheatCL->setEnabled(true);

        formLayout->setWidget(4, QFormLayout::LabelRole, wheatCL);

        wheatCIN = new QSpinBox(layoutWidget);
        wheatCIN->setObjectName(QStringLiteral("wheatCIN"));
        wheatCIN->setEnabled(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, wheatCIN);

        Debug = new QLabel(centralwidget);
        Debug->setObjectName(QStringLiteral("Debug"));
        Debug->setGeometry(QRect(240, 163, 91, 20));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 358, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNo_Tools_yet);
        menuTools->addAction(actionModify);
        menuTools->addAction(actionNew_ENVVAR_dir);
        menuHelp->addAction(actionHelp_me_please);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Bread Count", 0));
        actionEnviromentVars->setText(QApplication::translate("MainWindow", "EnviromentVars", 0));
        actionModify->setText(QApplication::translate("MainWindow", "Modify", 0));
        actionNew_ENVVAR_dir->setText(QApplication::translate("MainWindow", "New ENVVAR dir", 0));
        actionRound->setText(QApplication::translate("MainWindow", "Round", 0));
        actionHelp_me_please->setText(QApplication::translate("MainWindow", "How does this crap work", 0));
        actionNo_Tools_yet->setText(QApplication::translate("MainWindow", "No Tools yet", 0));
        showBread->setText(QApplication::translate("MainWindow", "Show", 0));
        whiteL->setText(QApplication::translate("MainWindow", "White Count:", 0));
        wheatL->setText(QApplication::translate("MainWindow", "Wheat Count:", 0));
        catPrompt->setText(QApplication::translate("MainWindow", "Catering: ", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", 0)
         << QApplication::translate("MainWindow", "Mixed", 0)
         << QApplication::translate("MainWindow", "Custom", 0)
        );
        whiteCL->setText(QApplication::translate("MainWindow", "Catering White", 0));
        wheatCL->setText(QApplication::translate("MainWindow", "Catering Wheat", 0));
        Debug->setText(QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Vars", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
