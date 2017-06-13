
LIBSOURCE = source-$$DEVICE

CONFIG(debug, debug|release) {
    LIBSOURCE = $$join(LIBSOURCE,,,"-debug")
}

LIBS += -L$$PWD/lib -l$$LIBSOURCE
