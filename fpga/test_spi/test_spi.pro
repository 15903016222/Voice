QT += core quick
QT -= gui

DEVICE = PHASCAN_II

DEFINES += $$DEVICE

CONFIG += c++11

TARGET = test_spi
CONFIG += console
CONFIG -= app_bundle

target.path = /home/root

INSTALLS += target

TEMPLATE = app

SOURCES += main.cpp \
    ../spi.cpp \
    ../fpga_spi.cpp

HEADERS += \
    ../spi.h \
    ../fpga_spi.h
