TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    shapeapi.h


CONFIG (debug, debug|release) {
LIBS += "..\test_3d\Lib\debug\ShapeAPI.dll"
}else{
LIBS += "..\test_3d\Lib\release\ShapeAPI.dll"
}
