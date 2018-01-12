
include($$PWD/line/line.pri)
include($$PWD/ruler/ruler.pri)
include($$PWD/color_bar/color_bar.pri)

include($$PWD/cursor/cursor.pri)

include($$PWD/base/base.pri)
include($$PWD/a_scan/a_scan.pri)
include($$PWD/b_scan/b_scan.pri)
include($$PWD/c_scan/c_scan.pri)
include($$PWD/s_scan/s_scan.pri)
include($$PWD/fft/fft.pri)

SOURCES += \
    $$PWD/display_widget.cpp \
    $$PWD/test_stub.cpp


HEADERS += \
    $$PWD/display_widget.h \
    $$PWD/test_stub.h
