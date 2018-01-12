
TRANSLATIONS += \
    $$PWD/resource/translate/Chinese.ts \
    $$PWD/resource/translate/Russian.ts \
    $$PWD/resource/translate/Japanese.ts \
    $$PWD/resource/translate/German.ts \
    $$PWD/resource/translate/Franch.ts

RESOURCES += \
    $$PWD/main_window.qrc

include($$PWD/common/common.pri)

include($$PWD/main_window/main_window.pri)

include($$PWD/measure_bar/measure_bar.pri)

include($$PWD/icons_bar/icons_bar.pri)

include($$PWD/status_bar/status_bar.pri)

include($$PWD/dialog/dialog.pri)

include($$PWD/menu/menu.pri)

include($$PWD/vinput/vinput.pri)

include($$PWD/display/display.pri)

include($$PWD/tool/tool.pri)

include($$PWD/wizard/wizard.pri)

