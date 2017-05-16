
INCLUDEPATH += $$PWD

RESOURCES += \
    $$PWD/main_window.qrc

include(main_window/main_window.pri)

include(icons_bar/icons_bar.pri)

include(dialog/dialog.pri)

include(measure_bar/measure_bar.pri)

include(menu/menu.pri)

include(vinput/vinput.pri)

include(display/display.pri)

include(display/dxf/dxf.pri)
