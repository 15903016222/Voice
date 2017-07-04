
PUBLIC_HEADERS += \
    $$PWD/device.h \
    $$PWD/group.h

PRIVATE_HEADERS += \
    $$PWD/device_p.h

SOURCES += \
    $$PWD/device.cpp \
    $$PWD/group.cpp \
    $$PWD/gate.cpp \
    $$PWD/sample.cpp

pcwin {
    SOURCES += $$PWD/device_pcwin.cpp
}

pcunix {
    SOURCES += $$PWD/device_pcunix.cpp
}

phascan {
    SOURCES += \
        $$PWD/device_phascan.cpp \
        $$PWD/cert.cpp
    HEADERS += \
        $$PWD/cert.h
}

phascan_ii {
    SOURCES += \
        $$PWD/device_phascan_ii.cpp \
        $$PWD/cert.cpp
    HEADERS += \
        $$PWD/cert.h
}

HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS \
    $$PWD/gate.h \
    $$PWD/sample.h
