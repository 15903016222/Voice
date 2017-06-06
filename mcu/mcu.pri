
LIBMCU = mcu-$$DEVICE
CONFIG(debug, debug|release) {
    LIBMCU = $$join(LIBMCU,,,"-debug")
}

LIBS += -L$$PWD/lib -l$$LIBMCU

