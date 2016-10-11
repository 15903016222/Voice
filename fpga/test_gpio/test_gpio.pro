#-------------------------------------------------
#
# Project created by QtCreator 2016-09-18T16:22:32
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testgpio
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testgpio.cpp \
    ../gpio.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../gpio.h
