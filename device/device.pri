INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/device.h

equals(DEVICE, "PC_UNIX") {
    SOURCES += \
        $$PWD/device_pc.cpp
}


equals(DEVICE, "PHASCAN"){
    HEADERS += \
        $$PWD/cert.h \
    SOURCES += \
        $$PWD/device_phascan.cpp \
        $$PWD/cert.cpp
}
