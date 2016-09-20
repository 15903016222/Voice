#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T14:21:21
#
#-------------------------------------------------

QT      += core gui

equals(QT_MAJOR_VERSION, 5) {
    QT      += serialport
    DEFINES += PHASCAN_II
}

equals(QT_MAJOR_VERSION, 4) {
    CONFIG  += serialport
    QMAKE_CXXFLAGS += -Wno-psabi
    DEFINES += PHASCAN
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../mcu_imx.cpp \
    ../mcu_omap.cpp \
    ../mcu.cpp

HEADERS  += mainwindow.h \
    ../mcu.h \
    ../mcu_imx.h \
    ../mcu_omap.h \
    ../probe.h

FORMS    += mainwindow.ui
