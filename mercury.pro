#-------------------------------------------------
#
# Project created by QtCreator 2016-07-26T15:13:49
#
#-------------------------------------------------

QT       += core gui

equals(QT_MAJOR_VERSION, 5) {
    QT      += serialport
    DEFINES += PHASCAN_II
}

equals(QT_MAJOR_VERSION, 4) {
    CONFIG  += serialport
    QMAKE_CXXFLAGS += -Wno-psabi
    DEFINES += PHASCAN
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
INCLUDEPATH += $$PWD/mcu
#INCLUDEPATH += $$PWD/sourcedata

INCLUDEPATH += $$PWD/lib/qjson/lib
DEPENDPATH += $$PWD/lib/qjson/lib

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
    mcu/mcu.cpp \
    mcu/mcu_imx.cpp \
    mcu/mcu_omap.cpp
#    sourcedata/dmaoperate.cpp \
#    sourcedata/phascanidata.cpp \
#    sourcedata/sourcedata.cpp

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
    mcu/mcu.h \
    mcu/mcu_imx.h \
    mcu/mcu_omap.h \
    mcu/probe.h
#    sourcedata/dmaoperate.h \
#    sourcedata/phascanidata.h \
#    sourcedata/sourcedata.h

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
    ui/dialogwidget/verticalsliderdialog.ui

DISTFILES += \
    ui/resources/menu.json \
    ui/resources/menuone.json \
    ui/resources/menuthree.json \
    ui/resources/menutwo.json \
    ui/resources/menucache.json

win32 {
    LIBS += -L$$PWD/lib/qjson/lib/ -llibqjson-qt5.dll
}

unix {
    LIBS += -L$$PWD/lib/qjson/lib/ -lqjson
    PRE_TARGETDEPS += $$PWD/lib/qjson/lib/libqjson.a

    INCLUDEPATH += /stuff/bitbake/bin/tmp/sysroots/i686-linux/usr/qt-4.8.6/lib/
    LIBS += -lQtGui
}

message($$CONFIG)
