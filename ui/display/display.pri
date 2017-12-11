
include($$PWD/ruler/ruler.pri)
include($$PWD/a_scan/a_scan.pri)
include($$PWD/b_scan/b_scan.pri)
include($$PWD/c_scan/c_scan.pri)
include($$PWD/s_scan/s_scan.pri)
include($$PWD/fft/fft.pri)

SOURCES += \
    $$PWD/scan_view.cpp \
    $$PWD/color_bar.cpp \
    $$PWD/display_widget.cpp \
    $$PWD/base_image_item.cpp \
    $$PWD/encoder_image_item.cpp \
    $$PWD/time_image_item.cpp \
    $$PWD/base_cursor_item.cpp \
    $$PWD/test_stub.cpp


HEADERS += \
    $$PWD/scan_view.h \
    $$PWD/color_bar.h \
    $$PWD/display_widget.h \
    $$PWD/base_image_item.h \
    $$PWD/encoder_image_item.h \
    $$PWD/time_image_item.h \
    $$PWD/base_cursor_item.h \
    $$PWD/test_stub.h


FORMS += \
    $$PWD/scan_display.ui
