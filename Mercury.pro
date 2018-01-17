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

    linux-arm-g++ {
    DEVICE = phascan
    }

    linux-oe-g++ {
    DEVICE = phascan_ii
    }
}

QMAKE_CXXFLAGS += -Wfatal-errors -Wall -Wextra #-Werror
QMAKE_CXXFLAGS_RELEASE += -O2

CONFIG += $$DEVICE
DEFINES += $$upper($$DEVICE)

target.path = /home/root
INSTALLS += target

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

equals(QT_MAJOR_VERSION, 4) {
    QMAKE_CXXFLAGS += -Wno-psabi
}

TARGET = Mercury
TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += include

include(device/device.pri)

include(ut/ut.pri)

include(gate/gate.pri)

include(sizing/sizing.pri)

include(display/display.pri)

include(measure/measure.pri)

include(ui/ui.pri)

### libs ###

include(mcu/mcu.pri)

include(fpga/fpga.pri)

include(source/source.pri)

include(focallaw/focallaw.pri)

include(configuration/configuration.pri)

