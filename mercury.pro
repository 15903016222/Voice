#-------------------------------------------------
#
# Project created by QtCreator 2016-07-26T15:13:49
#
#-------------------------------------------------

#-------------------------------------------------
# Support Devices:
#  PHASCAN
#  PHASCAN_II
#-------------------------------------------------

DEVICE = PC

DEFINES += $$DEVICE

QT       += core gui

equals(QT_MAJOR_VERSION, 5) {
    QT      += serialport
}

equals(QT_MAJOR_VERSION, 4) {
    CONFIG  += serialport
    QMAKE_CXXFLAGS += -Wno-psabi
}


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RESOURCES += ui/mainwindow.qrc

TRANSLATIONS += \
    ui/translator/phascanII_UI_Chinese.ts \
    ui/translator/phascanII_UI_English.ts

CODECFORTR = utf-8

TARGET = Mercury
TEMPLATE = app

PROJECT_DIR = $$PWD

INCLUDEPATH += $$PWD/ui
INCLUDEPATH += $$PWD/ui/menuwidget
INCLUDEPATH += $$PWD/ui/dialogwidget
INCLUDEPATH += $$PWD/ui/qitemdelegate

SOURCES += \
    main.cpp \
    ui/mainwindow.cpp \
    ui/iconswidget.cpp \
    ui/showinfowidget.cpp \
    ui/menuwidget/topmenu.cpp \
    ui/menuwidget/firstsecondmenuwidget.cpp \
    ui/menuwidget/thirdmenuwidget.cpp \
    ui/menuwidget/commonmenuwidget.cpp \
    ui/menuwidget/commonmenubutton.cpp \
    ui/dialogwidget/measurementdialog.cpp \
    ui/dialogwidget/myinputpanel.cpp \
    ui/dialogwidget/timesetdialog.cpp \
    ui/dialogwidget/probedialog.cpp \
    ui/dialogwidget/wedgedialog.cpp \
    ui/qitemdelegate/comboboxdelegate.cpp \
    ui/qitemdelegate/doublespinboxdelegate.cpp \
    ui/qitemdelegate/pushbuttondelegate.cpp \
    ui/dialogwidget/inputpanelcontext.cpp \
    ui/dialogwidget/verticalsliderdialog.cpp \
    ui/dialogwidget/resetconfigdialog.cpp \
    ui/dialogwidget/aboutdialog.cpp \
    ui/dialogwidget/creditsdialog.cpp \
    ui/dialogwidget/systeminfodialog.cpp \
    ui/dialogwidget/networkdialog.cpp \
    ui/dialogwidget/datetimesetdialog.cpp \
    ui/dialogwidget/filemanagerdialog.cpp

HEADERS += \
    ui/mainwindow.h \
    ui/iconswidget.h \
    ui/showinfowidget.h \
    ui/menuwidget/topmenu.h \
    ui/menuwidget/firstsecondmenuwidget.h \
    ui/menuwidget/thirdmenuwidget.h \
    ui/menuwidget/commonmenuwidget.h \
    ui/menuwidget/commonmenubutton.h \
    ui/dialogwidget/measurementdialog.h \
    ui/dialogwidget/myinputpanel.h \
    ui/dialogwidget/timesetdialog.h \
    ui/dialogwidget/probedialog.h \
    ui/dialogwidget/wedgedialog.h \
    ui/qitemdelegate/comboboxdelegate.h \
    ui/qitemdelegate/doublespinboxdelegate.h \
    ui/qitemdelegate/pushbuttondelegate.h \
    ui/dialogwidget/inputpanelcontext.h \
    ui/dialogwidget/verticalsliderdialog.h \
    ui/dialogwidget/resetconfigdialog.h \
    ui/dialogwidget/aboutdialog.h \
    ui/dialogwidget/creditsdialog.h \
    ui/dialogwidget/systeminfodialog.h \
    ui/dialogwidget/networkdialog.h \
    ui/dialogwidget/datetimesetdialog.h \
    ui/dialogwidget/filemanagerdialog.h

FORMS += \
    ui/mainwindow.ui \
    ui/iconswidget.ui \
    ui/showinfowidget.ui \
    ui/menuwidget/topmenu.ui \
    ui/menuwidget/firstsecondmenuwidget.ui \
    ui/menuwidget/thirdmenuwidget.ui \
    ui/menuwidget/commonmenuwidget.ui \
    ui/menuwidget/commonmenubutton.ui \
    ui/dialogwidget/measurementdialog.ui \
    ui/dialogwidget/myinputpanel.ui \
    ui/dialogwidget/timesetdialog.ui \
    ui/dialogwidget/probedialog.ui \
    ui/dialogwidget/wedgedialog.ui \
    ui/dialogwidget/inputpanelcontext.ui \
    ui/dialogwidget/verticalsliderdialog.ui \
    ui/dialogwidget/resetconfigdialog.ui \
    ui/dialogwidget/aboutdialog.ui \
    ui/dialogwidget/creditsdialog.ui \
    ui/dialogwidget/systeminfodialog.ui \
    ui/dialogwidget/networkdialog.ui \
    ui/dialogwidget/datetimesetdialog.ui \
    ui/dialogwidget/filemanagerdialog.ui


include(lib/lib.pri)

include(device/device.pri)
include(mcu/mcu.pri)

unix {
    INCLUDEPATH += /stuff/bitbake/bin/tmp/sysroots/i686-linux/usr/qt-4.8.6/lib/
#    LIBS += -lQtGui
}

message($$CONFIG)
