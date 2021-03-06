INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/mcu.h

SOURCES += \
    $$PWD/mcu.cpp

equals(QT_MAJOR_VERSION, 5) {
    QT      += serialport
}

equals(QT_MAJOR_VERSION, 4) {
    CONFIG  += serialport
}

equals(DEVICE, "PC_UNIX") {
    HEADERS += \
        $$PWD/mcu_pc.h
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
