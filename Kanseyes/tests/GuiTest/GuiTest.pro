#-------------------------------------------------
#
# Project created by QtCreator 2013-09-20T15:08:18
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuiTest
TEMPLATE = app

include(c:/Dev/Qwt-6.1.0/features/qwt.prf)
SOURCES += main.cpp \
    ../../src/Plot.cpp \
    ../../src/Model.cpp \
    ../../src/Data.cpp \
    ../../src/Curves.cpp \
    ../../src/PlotCurve.cpp \
    ../../src/View.cpp \
    ../../src/Plots.cpp \
    ../../src/MainWindow.cpp \
    ../../src/ProgController.cpp \
    ../../src/DataUDP.cpp \
    ../../src/Settings.cpp \
    ../../src/IntDelegate.cpp \
    ../../src/HeaderDelegate.cpp \
    ../../src/HeadersModel.cpp \
    ../../src/Headers.cpp


HEADERS  += \
    ../../src/Model.h \
    ../../src/global.h \
    ../../src/Data.h \
    ../../src/Curves.h \
    ../../src/Plot.h \
    ../../src/PlotCurve.h \
    ../../src/View.h \
    ../../src/Plots.h \
    ../../src/MainWindow.h \
    ../../src/ProgController.h \
    ../../src/DataUDP.h \
    ../../src/Settings.h \
    ../../src/HeaderDelegate.h \
    ../../src/IntDelegate.h \
    ../../src/Headers.h \
    ../../src/HeadersModel.h

FORMS += \
    ../../src/View.ui \
    ../../src/MainWindow.ui \
    ../../src/Settings.ui \
    ../../src/Headers.ui

RESOURCES += \
    ../../src/res.qrc
