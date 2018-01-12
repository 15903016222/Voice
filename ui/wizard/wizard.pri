
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

include(weld/weld.pri)
include(calibration/calibration.pri)
include(focallaw/focallaw.pri)
include(multi_group/multi_group.pri)
include(probe_part/probe_part.pri)
include(setting/setting.pri)

