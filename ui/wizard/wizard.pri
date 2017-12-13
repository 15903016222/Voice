
INCLUDEPATH += $$PWD

SOURCES += \
        $$PWD/wizard.cpp \
    $$PWD/wizard_setting.cpp \
    $$PWD/step_widget.cpp \
    $$PWD/workpiece_probe_widget.cpp \
    $$PWD/focallaw_widget.cpp \
    $$PWD/calibration_widget.cpp \
    $$PWD/multi_group_widget.cpp \
    $$PWD/selector.cpp \
    $$PWD/encoder_properties_widget.cpp \
    $$PWD/sound_velocity_properties_widget.cpp \
    $$PWD/delay_properties_widget.cpp \
    $$PWD/acg_properties_widget.cpp \
    $$PWD/tcg_properties_widget.cpp \
    $$PWD/ut_detect_setting_widget.cpp \
    $$PWD/pa_detect_setting_widget.cpp \
    $$PWD/common_setting_widget.cpp \
    $$PWD/tofd_properties_widget.cpp \
    $$PWD/angle_properties_widget.cpp \
    $$PWD/sub_wizard_setting.cpp \
    $$PWD/base_open_file_dialog.cpp
HEADERS += \
        $$PWD/wizard.h \
    $$PWD/wizard_setting.h \
    $$PWD/step_widget.h \
    $$PWD/workpiece_probe_widget.h \
    $$PWD/focallaw_widget.h \
    $$PWD/calibration_widget.h \
    $$PWD/multi_group_widget.h \
    $$PWD/selector.h \
    $$PWD/encoder_properties_widget.h \
    $$PWD/sound_velocity_properties_widget.h \
    $$PWD/delay_properties_widget.h \
    $$PWD/acg_properties_widget.h \
    $$PWD/tcg_properties_widget.h \
    $$PWD/ut_detect_setting_widget.h \
    $$PWD/pa_detect_setting_widget.h \
    $$PWD/common_setting_widget.h \
    $$PWD/tofd_properties_widget.h \
    $$PWD/angle_properties_widget.h \
    $$PWD/sub_wizard_setting.h \
    $$PWD/base_open_file_dialog.h

FORMS += \
    $$PWD/wizard.ui \
    $$PWD/wizard_setting.ui \
    $$PWD/step_widget.ui \
    $$PWD/workpiece_probe_widget.ui \
    $$PWD/focallaw_widget.ui \
    $$PWD/calibration_widget.ui \
    $$PWD/multi_group_widget.ui \
    $$PWD/encoder_properties_widget.ui \
    $$PWD/sound_velocity_properties_widget.ui \
    $$PWD/delay_properties_widget.ui \
    $$PWD/acg_properties_widget.ui \
    $$PWD/tcg_properties_widget.ui \
    $$PWD/ut_detect_setting_widget.ui \
    $$PWD/pa_detect_setting_widget.ui \
    $$PWD/common_setting_widget.ui \
    $$PWD/tofd_properties_widget.ui \
    $$PWD/angle_properties_widget.ui \
    $$PWD/base_open_file_dialog.ui


include(weld/weld.pri)

