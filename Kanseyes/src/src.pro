#-------------------------------------------------
#
# Project created by QtCreator 2013-09-18T13:51:56
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kanseyes
DESTDIR = $$PWD/../../installer
TEMPLATE = app

include($$PWD/Plot.pri)
include($$PWD/Auxiliary.pri)
include($$PWD/Receiver.pri)
include($$PWD/Gui.pri)
include(c:\Dev\Qt\Qt5.2.1\Qwt-6.1.0\features\qwt.prf)

SOURCES += main.cpp

HEADERS  +=

RESOURCES += \
    res.qrc


