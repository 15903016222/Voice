HEADERS += \
    $$PWD/report.h \
    $$PWD/base_report.h \
    $$PWD/report_defects.h \
    $$PWD/report_encoder.h \
    $$PWD/report_fft.h \
    $$PWD/report_gate.h \
    $$PWD/report_groups.h \
    $$PWD/report_header.h \
    $$PWD/report_law.h \
    $$PWD/report_part.h \
    $$PWD/report_probe.h \
    $$PWD/report_setup.h \
    $$PWD/report_users.h \
    $$PWD/report_wedge.h \
    $$PWD/report_scan.h \
    $$PWD/report_group.h \
    $$PWD/report_data.h

SOURCES += \
    $$PWD/report.cpp \
    $$PWD/base_report.cpp \
    $$PWD/report_defects.cpp \
    $$PWD/report_encoder.cpp \
    $$PWD/report_fft.cpp \
    $$PWD/report_gate.cpp \
    $$PWD/report_groups.cpp \
    $$PWD/report_header.cpp \
    $$PWD/report_law.cpp \
    $$PWD/report_part.cpp \
    $$PWD/report_probe.cpp \
    $$PWD/report_scan.cpp \
    $$PWD/report_setup.cpp \
    $$PWD/report_users.cpp \
    $$PWD/report_wedge.cpp \
    $$PWD/report_group.cpp \
    $$PWD/report_data.cpp

INCLUDEPATH += $$PWD/lua5.1

LIBLUA = lua-$$DEVICE

LIBS += -L$$PWD/lua5.1 -l$$LIBLUA
