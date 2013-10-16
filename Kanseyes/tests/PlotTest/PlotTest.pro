#-------------------------------------------------
#
# Project created by QtCreator 2013-09-18T14:07:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlotTest
TEMPLATE = app

include(c:/Dev/Qwt-6.0.1/features/qwt.prf)

SOURCES += main.cpp \
    ../../src/Plot.cpp \
    ../../src/Model.cpp \
    ../../src/Data.cpp \
    ../../src/Curves.cpp \
    ../../src/Command.cpp \
    ../../src/PlotCurve.cpp \
    ../../src/View.cpp \
    ../../src/IntDelegate.cpp \
    ../../src/HeaderDelegate.cpp \
    ../../src/HeadersModel.cpp \
    ../../src/Headers.cpp

HEADERS  += \
    ../../src/Model.h \
    ../../src/global.h \
    ../../src/Data.h \
    ../../src/Curves.h \
    ../../src/Command.h \
    ../../src/Plot.h \
    ../../src/PlotCurve.h \
    ../../src/View.h \
    ../../src/HeaderDelegate.h \
    ../../src/IntDelegate.h \
    ../../src/Headers.h \
    ../../src/HeadersModel.h

FORMS += \
    ../../src/View.ui \
    ../../src/Headers.ui

RESOURCES += \
    ../../src/res.qrc
