
include($$PWD/general/general.pri)
include($$PWD/pulser/pulser.pri)
include($$PWD/receiver/receiver.pri)

HEADERS += \
    $$PWD/general_menu.h \
    $$PWD/pulser_menu.h \
    $$PWD/receiver_menu.h \
    $$PWD/ut_advanced_menu.h

SOURCES += \
    $$PWD/general_menu.cpp \
    $$PWD/pulser_menu.cpp \
    $$PWD/receiver_menu.cpp \
    $$PWD/ut_advanced_menu.cpp
