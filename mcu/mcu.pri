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

pcunix {
    HEADERS += \
        $$PWD/mcu_pc.h
}

phascan {
    HEADERS += \
        $$PWD/mcu_omap.h

    SOURCES += \
        $$PWD/mcu_omap.cpp
}

phascan_ii {
    HEADERS += \
        $$PWD/mcu_imx.h

    SOURCES += \
        $$PWD/mcu_imx.cpp
}
