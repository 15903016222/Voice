
LIBSOURCE = Source_$$DEVICE

CONFIG(debug, debug|release) {
    LIBSOURCE = $$join(LIBSOURCE,,,_debug)
}

message($$DEVICE)

LIBS += -L$$PWD/lib -l$$LIBSOURCE
