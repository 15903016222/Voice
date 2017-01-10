#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T17:38:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_probe
TEMPLATE = app

target.path = /home/root
INSTALLS += target

SOURCES += main.cpp\
        mainwindow.cpp \
        ../probe.cpp

HEADERS  += mainwindow.h \
        ../probe.h

FORMS    += mainwindow.ui
