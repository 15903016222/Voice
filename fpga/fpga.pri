
LIBFPGA = fpga-$$DEVICE
CONFIG(debug, debug|release) {
    LIBFPGA = $$join(LIBFPGA,,,"-debug")
}

LIBS += -L$$PWD/lib -l$$LIBFPGA

