
HEADERS += \
    $$PWD/focallaw.h \
    $$PWD/point.h

LIBFOCALLAW = Focallaw_$$DEVICE
CONFIG(debug, debug|release) {
    LIBFOCALLAW = $$join(LIBFOCALLAW,,,_debug)
}

LIBS += -L$$PWD/lib -l$$LIBFOCALLAW
