

INCLUDEPATH +=$$PWD
INCLUDEPATH +=./ui/display

HEADERS += \
    $$PWD/main_weld_widget.h \
    $$PWD/static_weld_widget.h \
    $$PWD/weld_properties_widget.h 

SOURCES += \
    $$PWD/main_weld_widget.cpp \
    $$PWD/static_weld_widget.cpp \
    $$PWD/weld_properties_widget.cpp 


FORMS += \
    $$PWD/main_weld_widget.ui \
    $$PWD/static_weld_widget.ui \
    $$PWD/weld_properties_widget.ui 

include(weld_widget/weld_widget.pri)
