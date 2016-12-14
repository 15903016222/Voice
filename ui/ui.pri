
INCLUDEPATH += $$PWD

RESOURCES += \
    $$PWD/main_window.qrc

include(main_window/main_window.pri)

include(icons_bar/icons_bar.pri)

include(dialog/dialog.pri)

include(measure_bar/measure_bar.pri)

include(menu/menu.pri)

include(qitemdelegate/qitemdelegate.pri)

include(vinput/vinput.pri)

include(scan_layout/scan_layout.pri)

#include(display/display.pri)

include(config/config.pri)
