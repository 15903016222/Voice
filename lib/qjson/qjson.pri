INCLUDEPATH += $$PWD

DEFINES += QJSON_STATIC YYDEBUG=0

SOURCES += \ 
    $$PWD/json_parser.cc \
    $$PWD/json_scanner.cc \
    $$PWD/json_scanner.cpp \
    $$PWD/parser.cpp \
    $$PWD/parserrunnable.cpp \
    $$PWD/qobjecthelper.cpp \
    $$PWD/serializer.cpp \
    $$PWD/serializerrunnable.cpp
HEADERS  += \ 
    $$PWD/FlexLexer.h \
    $$PWD/json_parser.hh \
    $$PWD/json_scanner.h \
    $$PWD/location.hh \
    $$PWD/parser.h \
    $$PWD/parser_p.h \
    $$PWD/parserrunnable.h \
    $$PWD/position.hh \
    $$PWD/qjson_debug.h \
    $$PWD/qjson_export.h \
    $$PWD/qobjecthelper.h \
    $$PWD/serializer.h \
    $$PWD/serializerrunnable.h \
    $$PWD/stack.hh
