
INCLUDEPATH += $$PWD/msgpack
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/configuration.h \
    $$PWD/base_item_config.h \
    $$PWD/preference_config.h \
    $$PWD/group_config.h

SOURCES += \
    $$PWD/configuration.cpp \
    $$PWD/base_item_config.cpp \
    $$PWD/preference_config.cpp \
    $$PWD/group_config.cpp

LIBMSGPACK = msgpackc

LIBS += -L$$PWD/lib -l$$LIBMSGPACK


