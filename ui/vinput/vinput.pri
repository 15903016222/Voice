
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/vinput.h

pcwin {
    SOURCES += \
        $$PWD/vinput_pcwin.cpp
}

pcunix {
    SOURCES += \
        $$PWD/vinput_pcunix.cpp
}

phascan {
    SOURCES += \
        $$PWD/vinput_phascan.cpp
}

phascan_ii {
    SOURCES += \
        $$PWD/vinput_phascan_ii.cpp
}
