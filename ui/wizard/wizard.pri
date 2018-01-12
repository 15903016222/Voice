
INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/wizard.cpp \
    $$PWD/wizard_setting.cpp \
    $$PWD/step_widget.cpp \
    $$PWD/selector.cpp \
    $$PWD/sub_wizard_setting.cpp

HEADERS += \
    $$PWD/wizard.h \
    $$PWD/wizard_setting.h \
    $$PWD/step_widget.h \
    $$PWD/selector.h \
    $$PWD/sub_wizard_setting.h

FORMS += \
    $$PWD/wizard.ui \
    $$PWD/wizard_setting.ui \
    $$PWD/step_widget.ui

include($$PWD/weld/weld.pri)

include($$PWD/calibration/calibration.pri)

include($$PWD/focallaw/focallaw.pri)

include($$PWD/multi_group/multi_group.pri)

include($$PWD/probe_part/probe_part.pri)

include($$PWD/setting/setting.pri)

