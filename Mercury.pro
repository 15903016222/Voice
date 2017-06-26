#-------------------------------------------------
#
# Project created by QtCreator 2016-07-26T15:13:49
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
    DEVICE = pcwin
}
unix {
    DEVICE = pcunix
    LIBS += -lX11 -lXtst

    linux-arm-g++ {
    DEVICE = phascan
    }

    linux-oe-g++ {
    DEVICE = phascan_ii
    }
}

CONFIG += $$DEVICE
DEFINES += $$upper($$DEVICE)

target.path = /home/root
INSTALLS += target

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

equals(QT_MAJOR_VERSION, 4) {
    QMAKE_CXXFLAGS += -Wno-psabi
}


TRANSLATIONS += \
    ui/translator/phascanII_UI_Chinese.ts \
    ui/translator/phascanII_UI_English.ts

TARGET = Mercury
TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += include

include(device/device.pri)

include(ui/ui.pri)

include(mcu/mcu.pri)

include(fpga/fpga.pri)

include(source/source.pri)
#include(Source/src/source-lib.pri)

include(focallaw/focallaw.pri)
