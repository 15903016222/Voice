
equals(DEVICE, "PC_WIN") {
	LIBFPGA = Fpga_Win
}
else: equals(DEVICE, "PHASCAN_II") {
      LIBFPGA = Fpga_Phascan_II
}
else: equals(DEVICE, "PHASCAN") {
      LIBFPGA = Fpga_Phascan
}
else: equals(DEVICE, "PC_UNIX") {
      LIBFPGA = Fpga_Linux
}

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
