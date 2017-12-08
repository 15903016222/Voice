
include($$PWD/a_scan/a_scan.pri)
include($$PWD/s_scan/s_scan.pri)

SOURCES += \
    $$PWD/ruler_widget.cpp \
    $$PWD/scan_view.cpp \
    $$PWD/color_bar.cpp \
    $$PWD/display_widget.cpp \
    $$PWD/c_scan_display.cpp \
    $$PWD/c_scan_hdisplay.cpp \
    $$PWD/c_scan_vdisplay.cpp \
    $$PWD/c_scan_time_image_item.cpp \
    $$PWD/c_scan_encoder_image_item.cpp \
    $$PWD/c_scan_data.cpp \
    $$PWD/c_scan_scene.cpp \
    $$PWD/b_scan_display.cpp \
    $$PWD/b_scan_scene.cpp \
    $$PWD/b_scan_hdisplay.cpp \
    $$PWD/b_scan_vdisplay.cpp \
    $$PWD/scroll_ruler_widget.cpp \
    $$PWD/b_scan_encoder_image_item.cpp \
    $$PWD/b_scan_time_image_item.cpp \
    $$PWD/base_image_item.cpp \
    $$PWD/encoder_image_item.cpp \
    $$PWD/test_stub.cpp \
    $$PWD/time_image_item.cpp \
    $$PWD/base_cursor_item.cpp \
    $$PWD/vdisplay_cursor_item.cpp \
    $$PWD/hdisplay_cursor_item.cpp   \
    $$PWD/fft_display.cpp \
    $$PWD/fft_hdisplay.cpp \
    $$PWD/fft_scene.cpp \
    $$PWD/fft_item.cpp \
    $$PWD/fft_calculator.cpp


HEADERS += \
    $$PWD/ruler_widget.h \
    $$PWD/scan_view.h \
    $$PWD/color_bar.h \
    $$PWD/display_widget.h \
    $$PWD/c_scan_display.h \
    $$PWD/c_scan_hdisplay.h \
    $$PWD/c_scan_vdisplay.h \
    $$PWD/c_scan_hdisplay.h \
    $$PWD/c_scan_time_image_item.h \
    $$PWD/c_scan_encoder_image_item.h \
    $$PWD/c_scan_data.h \
    $$PWD/c_scan_scene.h \
    $$PWD/b_scan_display.h \
    $$PWD/b_scan_scene.h \
    $$PWD/b_scan_hdisplay.h \
    $$PWD/b_scan_vdisplay.h \
    $$PWD/scroll_ruler_widget.h \
    $$PWD/b_scan_encoder_image_item.h \
    $$PWD/b_scan_time_image_item.h \
    $$PWD/base_image_item.h \
    $$PWD/encoder_image_item.h \
    $$PWD/test_stub.h \
    $$PWD/time_image_item.h \
    $$PWD/base_cursor_item.h \
    $$PWD/vdisplay_cursor_item.h \
    $$PWD/hdisplay_cursor_item.h \
    $$PWD/fft_display.h \
    $$PWD/fft_hdisplay.h \
    $$PWD/fft_scene.h \
    $$PWD/fft_item.h \
    $$PWD/fft_calculator.h


FORMS += \
    $$PWD/scan_display.ui \
    $$PWD/b_scan_display.ui \
    $$PWD/fft_display.ui
