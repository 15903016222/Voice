#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T14:12:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fpga_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../gpio.cpp

HEADERS  += mainwindow.h \
    ../gpio.h

FORMS    += mainwindow.ui
