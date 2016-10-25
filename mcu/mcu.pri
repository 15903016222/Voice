INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/mcu.h \
    $$PWD/probe.h \
    $$PWD/mcu_pc.h

SOURCES += \
    $$PWD/mcu.cpp

equals(QT_MAJOR_VERSION, 5) {
    QT      += serialport
}

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
