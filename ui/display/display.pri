
include($$PWD/a_scan/a_scan.pri)
include($$PWD/b_scan/b_scan.pri)
include($$PWD/c_scan/c_scan.pri)
include($$PWD/s_scan/s_scan.pri)

SOURCES += \
    $$PWD/ruler_widget.cpp \
    $$PWD/scan_view.cpp \
    $$PWD/color_bar.cpp \
    $$PWD/display_widget.cpp \
    $$PWD/scroll_ruler_widget.cpp \
    $$PWD/base_image_item.cpp \
    $$PWD/encoder_image_item.cpp \
    $$PWD/time_image_item.cpp \
    $$PWD/base_cursor_item.cpp \
    $$PWD/fft_display.cpp \
    $$PWD/fft_hdisplay.cpp \
    $$PWD/fft_scene.cpp \
    $$PWD/fft_item.cpp \
    $$PWD/fft_calculator.cpp \
    $$PWD/test_stub.cpp


HEADERS += \
    $$PWD/ruler_widget.h \
    $$PWD/scan_view.h \
    $$PWD/color_bar.h \
    $$PWD/display_widget.h \
    $$PWD/scroll_ruler_widget.h \
    $$PWD/base_image_item.h \
    $$PWD/encoder_image_item.h \
    $$PWD/time_image_item.h \
    $$PWD/base_cursor_item.h \
    $$PWD/fft_display.h \
    $$PWD/fft_hdisplay.h \
    $$PWD/fft_scene.h \
    $$PWD/fft_item.h \
    $$PWD/fft_calculator.h \
    $$PWD/test_stub.h


FORMS += \
    $$PWD/scan_display.ui \
    $$PWD/fft_display.ui
