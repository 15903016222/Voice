
INCLUDEPATH += $$PWD/include
DEPENDPATH  += $$PWD/include


equals(DEVICE, "PC_WIN") {
        LIBSOURCE = Source_Win
}
else: equals(DEVICE, "PHASCAN_II") {
      LIBSOURCE = Source_Phascan_II
}
else: equals(DEVICE, "PHASCAN") {
      LIBSOURCE = Source_Phascan
}
else: equals(DEVICE, "PC_UNIX") {
      LIBSOURCE = Source_Linux
}

CONFIG(debug, debug|release) {
    LIBSOURCE = $$join(LIBSOURCE,,,_debug)
}
LIBS += -L$$PWD/lib -l$$LIBSOURCE
