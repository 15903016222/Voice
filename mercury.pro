#-------------------------------------------------
#
# Project created by QtCreator 2016-07-26T15:13:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CFLAGS += -std=gnu99

RESOURCES += ui/mainwindow.qrc

#CONFIG+=precompile_header
#PRECOMPILED_HEADER=stable.h

TRANSLATIONS += \
    ui/translator/phascanII_UI_Chinese.ts \
    ui/translator/phascanII_UI_English.ts

CODECFORTR = utf-8

TARGET = Mercury
TEMPLATE = app

PROJECT_DIR = $$PWD


INCLUDEPATH += $$PWD/ui
INCLUDEPATH += $$PWD/ui/menuwidget
INCLUDEPATH += $$PWD/ui/qitemdelegate
INCLUDEPATH += $$PWD/ui/inputpanel

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
    ui/menuwidget/measurementdialog.cpp \
    ui/menuwidget/myinputpanel.cpp \
    ui/qitemdelegate/comboboxdelegate.cpp \
    ui/qitemdelegate/doublespinboxdelegate.cpp \
    ui/qitemdelegate/pushbuttondelegate.cpp \
    ui/menuwidget/probedialog.cpp \
    ui/menuwidget/wedgedialog.cpp

HEADERS += \
    ui/mainwindow.h \
    ui/iconswidget.h \
    ui/showinfowidget.h \
    ui/menuwidget/topmenu.h \
    ui/menuwidget/firstsecondmenuwidget.h \
    ui/menuwidget/thirdmenuwidget.h \
    ui/menuwidget/commonmenuwidget.h \
    ui/menuwidget/commonmenubutton.h \
    ui/menuwidget/measurementdialog.h \
    ui/menuwidget/myinputpanel.h \
    ui/qitemdelegate/comboboxdelegate.h \
    ui/qitemdelegate/doublespinboxdelegate.h \
    ui/qitemdelegate/pushbuttondelegate.h \
    ui/menuwidget/probedialog.h \
    ui/menuwidget/wedgedialog.h

FORMS += \
    ui/mainwindow.ui \
    ui/iconswidget.ui \
    ui/showinfowidget.ui \
    ui/menuwidget/topmenu.ui \
    ui/menuwidget/firstsecondmenuwidget.ui \
    ui/menuwidget/thirdmenuwidget.ui \
    ui/menuwidget/commonmenuwidget.ui \
    ui/menuwidget/commonmenubutton.ui \
    ui/menuwidget/measurementdialog.ui \
    ui/menuwidget/myinputpanel.ui \
    ui/menuwidget/probedialog.ui \
    ui/menuwidget/wedgedialog.ui

win32 {
#    CONFIG += windows link_prl
#    # boost
#    INCLUDEPATH += $$(BOOST_INCLUDE_PATH)
#    LIBS += -L$$(BOOST_LIB_PATH)
#    # LIBS += -lfooo # add fooo library

#    # GStreamer
#    INCLUDEPATH += $$(GSTREAMER_INCLUDE_PATH)
#    INCLUDEPATH += $$(GSTREAMER_INCLUDE_PATH)\\gstreamer-1.0
#    INCLUDEPATH += $$(GSTREAMER_INCLUDE_PATH)\\glib-2.0
#    INCLUDEPATH += $$(GSTREAMER_GLIB2_PRIVATE_INCLUDE_PATH)
#    INCLUDEPATH += $$(GSTREAMER_PRIVATE_INCLUDE_PATH)

#    LIBS += -L $$(GSTREAMER_LIB_PATH)

#    # Qt5Gstreamer
#    INCLUDEPATH += $$PROJECT_DIR\\lib\\win32\\Qt5GStreamer\\include
#    LIBS += -L$$PROJECT_DIR\\lib\\win32\\Qt5GStreamer\\lib

#    CONFIG(debug, debug|release){
#        LIBS += -lQt5GStreamerUid
#        LIBS += -lQt5GStreamerd
#        LIBS += -lQt5GLibd
#    }else{
#        LIBS += -lQt5GStreamerUi
#        LIBS += -lQt5GStreamer
#        LIBS += -lQt5GLib
#    }

#    LIBS += -lgstreamer-1.0
#    LIBS += -lgstvideo-1.0
#    LIBS += -lgstaudio-1.0
#    LIBS += -lgstpbutils-1.0
#    LIBS += -lgobject-2.0
#    LIBS += -lglib-2.0
#    DEFINES += QtGStreamer_Static

    CONFIG(release, debug|release): LIBS += -L$$PWD/lib/qjson/lib/ -llibqjson-qt5.dll
    else:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/qjson/lib/ -llibqjson-qt5.dll

    INCLUDEPATH += $$PWD/lib/qjson/lib
    DEPENDPATH += $$PWD/lib/qjson/lib
}

macx {
#    CONFIG += app_bundle

#    GSTREAM_FRAMEWORK_PATH=/Library/Frameworks/GStreamer.framework/Versions/Current
#    QTSTREAMER_LIB_BASE_PATH=$$PROJECT_DIR/lib/osx/gstreamer

#    message($$PROJECT_DIR)

#    QMAKE_LFLAGS += -F$$PROJECT_DIR/lib/osx/gstreamer
#    QMAKE_LFLAGS += -F/Library/Frameworks

#    LIBS += -framework GStreamer
#    LIBS += -framework QGlib
#    LIBS += -framework QtGStreamer
#    LIBS += -framework QtGStreamerUi

#    INCLUDEPATH += $$GSTREAM_FRAMEWORK_PATH/Headers
#    INCLUDEPATH += $$QTSTREAMER_LIB_BASE_PATH/QtGStreamer.framework/Headers
#    INCLUDEPATH += $$QTSTREAMER_LIB_BASE_PATH/QtGStreamerUi.framework/Headers
#    INCLUDEPATH += $$QTSTREAMER_LIB_BASE_PATH/QGLib.framework/Headers

#    FRAMEWORKS_FILES  = $$QTSTREAMER_LIB_BASE_PATH/QGLib.framework
#    FRAMEWORKS_FILES += $$QTSTREAMER_LIB_BASE_PATH/QtGStreamer.framework
#    FRAMEWORKS.files += $$QTSTREAMER_LIB_BASE_PATH/QtGStreamerUi.framework

#    FRAMEWORKS.path = Contents/Frameworks
#    QMAKE_BUNDLE_DATA += FRAMEWORKS

#    # boost
#    INCLUDEPATH += /usr/local/include

    LIBS += -L$$PWD/lib/qjson/lib/ -lqjson

    INCLUDEPATH += $$PWD/lib/qjson/lib
    DEPENDPATH += $$PWD/lib/qjson/lib
}

linux {

#    CONFIG += c++14

#    CONFIG += link_pkgconfig
#    PKGCONFIG += gstreamer-1.0

#    INCLUDEPATH += $$PROJECT_DIR/libs/linux/qtgstreamer/include/Qt5GStreamer

#    message($$PROJECT_DIR/libs/linux/qtgstreamer/include/Qt5Gstreamer)

#    # boost
#    INCLUDEPATH += /usr/include
#    INCLUDEPATH += /usr/local/include

#    LIBS += -L$$PROJECT_DIR/libs/linux/qtgstreamer/lib
#    LIBS += -lQt5GLib-2.0 -lQt5GStreamer-1.0 -lQt5GStreamerUi-1.0

    LIBS += -L$$PWD/lib/qjson/lib/ -lqjson

    INCLUDEPATH += $$PWD/lib/qjson/lib
    DEPENDPATH += $$PWD/lib/qjson/lib
}

message($$CONFIG)

DISTFILES += \
    ui/resources/menu.json \
    ui/resources/menuone.json \
    ui/resources/menuthree.json \
    ui/resources/menutwo.json \
    ui/resources/menucache.json
