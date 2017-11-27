
INCLUDEPATH += $$PWD/msgpack
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/configuration.h

SOURCES += \
    $$PWD/configuration.cpp

LIBMSGPACK = msgpackc

LIBS += -L$$PWD/lib -l$$LIBMSGPACK

