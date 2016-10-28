#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T08:56:44
#
#-------------------------------------------------

DEVICE = PHASCAN

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += $$DEVICE

TARGET = test_fpga
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../gpio.cpp \
    ../spi.cpp

HEADERS  += mainwindow.h \
    ../beam.h \
    ../fpga.h \
    ../gpio.h \
    ../group.h \
    ../spi.h

FORMS    += mainwindow.ui


equals(DEVICE, "PHASCAN") {
SOURCES += \
    ../beam_phascan.cpp \
    ../fpga_phascan.cpp \
    ../group_phascan.cpp \
    ../phascan_spi.cpp
HEADERS += \
    ../phascan_spi.h
}



equals(DEVICE, "PHASCAN_II") {

}
