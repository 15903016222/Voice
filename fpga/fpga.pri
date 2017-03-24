
LIBFPGA = Fpga_$$DEVICE
CONFIG(debug, debug|release) {
    LIBFPGA = $$join(LIBFPGA,,,_debug)
}
LIBS += -L$$PWD/lib -l$$LIBFPGA

HEADERS += \
    $$PWD/beam.h \
    $$PWD/fpga_global.h \
    $$PWD/fpga.h \
    $$PWD/group.h \
    $$PWD/tcg.h
