#-------------------------------------------------
#
# Project created by QtCreator 2016-10-12T10:00:25
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = devicetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += devicetest.cpp \
    ../device.cpp \
    ../cert.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../device.h \
    ../cert.h
