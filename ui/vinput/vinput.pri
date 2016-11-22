
INCLUDEPATH += $$PWD

#equals(DEVICE, "PC_WIN") {
#    SOURCES += \
#        $$PWD/vinput.cpp
#}

#equals(DEVICE, "PC_UNIX") {
#    SOURCES += \
#        $$PWD/vinput.cpp
#}

equals(DEVICE, "PHASCAN") {  
    HEADERS += \
        $$PWD/vinput.h
    SOURCES += \
        $$PWD/vinput.cpp
}

equals(DEVICE, "PHASCAN_II") {
    HEADERS += \
        $$PWD/vinput.h
    SOURCES += \
        $$PWD/vinput.cpp
}
