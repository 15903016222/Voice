INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/cert.h \
    $$PWD/device.h

SOURCES += \
    $$PWD/cert.cpp

equals(DEVICE, "PC_UNIX") {
    SOURCES += \
        $$PWD/device_pc.cpp
}


equals(DEVICE, "PHASCAN"){
    SOURCES += \
        $$PWD/device_phascan.cpp
}
