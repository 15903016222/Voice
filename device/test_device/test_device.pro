#-------------------------------------------------
#
# Project created by QtCreator 2016-10-12T10:00:25
#
#-------------------------------------------------

DEVICE = PHASCAN

QT       += testlib

QT       -= gui

TARGET   = devicetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


DEFINES += $$DEVICE

SOURCES += devicetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../device.pri)
