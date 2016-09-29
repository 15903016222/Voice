#-------------------------------------------------
#
# Project created by QtCreator 2016-09-18T16:07:47
#
#-------------------------------------------------
DEVICE = "PHASCAN"

QT       += testlib

QT       -= gui

TARGET = tst_testfpga
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


DEFINES += $$DEVICE

SOURCES += tst_testfpga.cpp \
    ../fpga.cpp \
    ../gpio.cpp \
    ../spi.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../fpga.h \
    ../gpio.h \
    ../spi.h \
    ../beam.h \
    ../group.h

equals(DEVICE, "PHASCAN") {
    SOURCES += \
        ../beam_phascan.cpp \
        ../group_phascan.cpp \
        ../phascan_spi.cpp

    HEADERS += \
        ../phascan_spi.h
}

equals(DEVICE, "PHASCAN_II") {
    SOURCES +=
    HEADERS +=
}
