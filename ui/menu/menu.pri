INCLUDEPATH += $$PWD

FORMS += \
    $$PWD/main_menu.ui \
    $$PWD/base_menu.ui

HEADERS += \
    $$PWD/main_menu.h \
    $$PWD/sub_menu.h \
    $$PWD/base_menu.h

SOURCES += \
    $$PWD/main_menu.cpp \
    $$PWD/sub_menu.cpp \
    $$PWD/base_menu.cpp

include($$PWD/menu_item/menu_item.pri)

include($$PWD/ut_setting/ut_setting.pri)
include($$PWD/gate_curves/gate_curves.pri)
include($$PWD/display/display.pri)
include($$PWD/probe_part/probe_part.pri)
include($$PWD/focal_law/focal_law.pri)
