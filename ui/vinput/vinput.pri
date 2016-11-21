
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/vinput.h

equals(DEVICE, "PC_WIN") {
    SOURCES += \
        $$PWD/vinput.cpp
}

equals(DEVICE, "PC_UNIX") {
    SOURCES += \
        $$PWD/vinput.cpp
}

equals(DEVICE, "PHASCAN") {
    SOURCES += \
        $$PWD/vinput.cpp
}

equals(DEVICE, "PHASCAN_II") {
    SOURCES += \
        $$PWD/vinput.cpp
}
