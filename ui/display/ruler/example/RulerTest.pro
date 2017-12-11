#-------------------------------------------------
#
# Project created by QtCreator 2017-12-09T22:02:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RulerTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include($$PWD/../src/ruler.pri)
INCLUDEPATH += $$PWD/../src/
