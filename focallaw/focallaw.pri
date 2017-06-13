
LIBFOCALLAW = focallaw-$$DEVICE

CONFIG(debug, debug|release) {
    LIBFOCALLAW = $$join(LIBFOCALLAW,,,"-debug")
}

LIBS += -L$$PWD/lib -l$$LIBFOCALLAW
