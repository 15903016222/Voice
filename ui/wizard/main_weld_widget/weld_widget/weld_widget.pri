

INCLUDEPATH +=$$PWD

HEADERS += \
    $$PWD/base_weld_information.h \
    $$PWD/base_weld_widget.h \
    $$PWD/global_property_tag.h \
    $$PWD/weld_information_factory.h \
    $$PWD/weld_widget_factory.h \
    $$PWD/weldwidget_global.h

LIBS += -L$$PWD/lib -lWeldWidget
