#-------------------------------------------------
#
# Project created by QtCreator 2016-08-16T17:29:01
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mercury
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mcu/mcu.cpp

HEADERS  += mainwindow.h \
    mcu/mcu.h
