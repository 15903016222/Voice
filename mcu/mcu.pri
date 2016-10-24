INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/mcu.h \
    $$PWD/probe.h

SOURCES += \
    $$PWD/mcu.cpp


equals(DEVICE, "PHASCAN") {
HEADERS += \
   $$PWD/mcu_omap.h

SOURCES += \
    $$PWD/mcu_omap.cpp
}

equals(DEVICE, "PHASCAN_II") {
HEADERS += \
    $$PWD/mcu_imx.h

SOURCES += \
    $$PWD/mcu_imx.cpp
}
