#-------------------------------------------------
#
# Project created by QtCreator 2016-07-26T15:13:49
#
#-------------------------------------------------

#------------------------------------------------------------
# Support Devices:
#  PC_UNIX    : Qt5.6.0, gcc.4.8.4
#  PC_WIN     : Qt5.7.0, MSVC2015
#  PHASCAN    : Qt4.8.6, arm-angstrom-linux-gnueabi-gcc.4.5.3
#  PHASCAN_II : Qt5.4.3, arm-phytec-linux-gnueabi-gcc.4.9.2
#-------------------------------------------------------------

DEVICE = PC_UNIX

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

equals(QT_MAJOR_VERSION, 4) {
    QMAKE_CXXFLAGS += -Wno-psabi
}

DEFINES += $$DEVICE

RESOURCES += ui/mainwindow.qrc

TRANSLATIONS += \
    ui/translator/phascanII_UI_Chinese.ts \
    ui/translator/phascanII_UI_English.ts

CODECFORTR = utf-8

TARGET = Mercury
TEMPLATE = app

PROJECT_DIR = $$PWD

SOURCES += main.cpp

include(ui/ui.pri)

include(lib/lib.pri)

include(device/device.pri)

include(mcu/mcu.pri)