FORMS += \
    $$PWD/main_menu.ui

HEADERS += \
    $$PWD/sub_menu.h \
    $$PWD/base_menu.h 

SOURCES += \
    $$PWD/sub_menu.cpp \
    $$PWD/base_menu.cpp 

include($$PWD/main_menu/main_menu.pri)
include($$PWD/menu_item/menu_item.pri)
include($$PWD/ut_setting/ut_setting.pri)
include($$PWD/gate_curves/gate_curves.pri)
include($$PWD/display/display.pri)
include($$PWD/probe_part/probe_part.pri)
include($$PWD/focal_law/focal_law.pri)
include($$PWD/scan/scan.pri)
include($$PWD/measurement/measurement.pri)
include($$PWD/file_report/file_report.pri)
include($$PWD/preference/preference.pri)
