
INCLUDEPATH += $$PWD/msgpack-2.1.5
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/configuration.h \
    $$PWD/base_item_config.h \
    $$PWD/preference_config.h \
    $$PWD/group_config.h \
    $$PWD/msgpack-2.1.5/msgpack.h \
    $$PWD/msgpack-2.1.5/msgpack.hpp

SOURCES += \
    $$PWD/configuration.cpp \
    $$PWD/base_item_config.cpp \
    $$PWD/preference_config.cpp \
    $$PWD/group_config.cpp
