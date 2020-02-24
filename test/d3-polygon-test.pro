TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD

include(../src/d3_polygon.pri)

SOURCES += \
    main.cpp

HEADERS += \
    area-test.hpp \
    centroid-test.hpp \
    contains-test.hpp \
    hull-test.hpp \
    length-test.hpp
