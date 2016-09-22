#-------------------------------------------------
#
# Project created by QtCreator 2016-09-18T16:07:47
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testfpga
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testfpga.cpp \
    ../fpga.cpp \
    ../gpio.cpp \
    ../omap_fpga.cpp \
    ../spi.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../fpga.h \
    ../gpio.h \
    ../omap_fpga.h \
    ../spi.h
