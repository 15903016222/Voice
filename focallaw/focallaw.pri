
LIBFOCALLAW = Focallaw_$$DEVICE
CONFIG(debug, debug|release) {
    LIBFOCALLAW = $$join(LIBFOCALLAW,,,_debug)
}

LIBS += -L$$PWD/lib -l$$LIBFOCALLAW

HEADERS += \
    $$PWD/beam.h \
    $$PWD/focallaw_global.h \
    $$PWD/probe.h \
    $$PWD/wedge.h \
    $$PWD/cylinder.h \
    $$PWD/focallaw.h \
    $$PWD/pa_probe.h \
    $$PWD/specimen.h \
    $$PWD/flat.h \
    $$PWD/point.h \
    $$PWD/ut_probe.h
