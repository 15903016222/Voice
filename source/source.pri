
LIBSOURCE = source-$$DEVICE

CONFIG(debug, debug|release) {
    LIBSOURCE = $$join(LIBSOURCE,,,"-debug")
}

LIBS += -L$$PWD/lib -l$$LIBSOURCE

HEADERS += \
    $$PWD/beam_group.h \
    $$PWD/beam.h \
    $$PWD/source.h \
    $$PWD/source_global.h
