HEADERS += \
    $$PWD/device.h \
    $$PWD/group.h

SOURCES += \
    $$PWD/device.cpp \
    $$PWD/group.cpp

equals(DEVICE, "PC_UNIX") {
    SOURCES += \
        $$PWD/device_pc.cpp
}

equals(DEVICE, "PC_WIN") {
    SOURCES += \
        $$PWD/device_pc.cpp
}

equals(DEVICE, "PHASCAN"){
    HEADERS += \
        $$PWD/cert.h \
        $$PWD/device_phascan.h
    SOURCES += \
        $$PWD/cert.cpp \
        $$PWD/device_phascan.cpp
}

equals(DEVICE, "PHASCAN_II") {
    HEADERS += \
        $$PWD/cert.h
    SOURCES += \
        $$PWD/cert.cpp \
        $$PWD/device_phascan_ii.cpp
}
