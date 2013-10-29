#-------------------------------------------------
#
# Project created by QtCreator 2013-10-23T18:06:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prj
TEMPLATE = app

RC_FILE = icon.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    breaddata.cpp \
    settings.cpp \
    resultwnd.cpp

HEADERS  += mainwindow.h \
    breaddata.h \
    settings.h \
    resultwnd.h

FORMS    += mainwindow.ui \
    settings.ui \
    resultwnd.ui
