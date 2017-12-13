#-------------------------------------------------
#
# Project created by QtCreator 2017-07-10T14:21:01
#
#-------------------------------------------------

QT       += widgets
#QT       -= gui

TARGET = WeldWidget
TEMPLATE = lib

DEFINES += WELDWIDGET_LIBRARY

SOURCES += \
    base_weld_information.cpp \
    base_weld_widget.cpp \
    i_weld_widget.cpp \
    i_weld_information.cpp \
    weld_widget_factory.cpp \
    weld_information_factory.cpp \
    v_weld_widget.cpp \
    v_weld_information.cpp \
    vv_weld_widget.cpp \
    vv_weld_information.cpp \
    vy_weld_widget.cpp \
    vy_weld_information.cpp \
    u_weld_widget.cpp \
    u_weld_information.cpp \
    uu_weld_information.cpp \
    uu_weld_widget.cpp \
    uv_weld_information.cpp \
    uv_weld_widget.cpp \
    tky_weld_information.cpp \
    tky_weld_widget.cpp

HEADERS +=\
        weldwidget_global.h \
    base_weld_information.h \
    base_weld_widget.h \
    i_weld_widget.h \
    i_weld_information.h \
    global_property_tag.h \
    weld_widget_factory.h \
    weld_information_factory.h \
    v_weld_widget.h \
    v_weld_information.h \
    vv_weld_widget.h \
    vv_weld_information.h \
    vy_weld_widget.h \
    vy_weld_information.h \
    u_weld_widget.h \
    u_weld_information.h \
    uu_weld_information.h \
    uu_weld_widget.h \
    uv_weld_information.h \
    uv_weld_widget.h \
    tky_weld_information.h \
    tky_weld_widget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
