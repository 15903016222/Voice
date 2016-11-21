#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T10:41:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vinput_test
TEMPLATE = app

#include(../vinput.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
        ../vinput.cpp

HEADERS  += mainwindow.h \
        ../vinput.h

FORMS    += mainwindow.ui
