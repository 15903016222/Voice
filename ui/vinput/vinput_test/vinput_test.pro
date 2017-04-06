#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T10:41:32
#
#-------------------------------------------------
#------------------------------------------------------------
# Support Devices:
#  UNIX       : Qt5.6.0, gcc.4.8.4
#  WIN        : Qt5.7.0, MSVC2015
#  PHASCAN    : Qt4.8.6, arm-angstrom-linux-gnueabi-gcc.4.5.3
#  PHASCAN_II : Qt5.4.3, arm-phytec-linux-gnueabi-gcc.4.9.2
#-------------------------------------------------------------

win32 {
DEVICE = win
}

linux-oe-g++ {
DEVICE = phascan_ii
LIBS += -lX11 -lXtst
}

linux-arm-g++ {
DEVICE = phascan
LIBS += -lX11 -lXtst
}

linux-g++ {
DEVICE = unix
LIBS += -lX11 -lXtst
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vinput_test
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include($$PWD/../vinput.pri)
