#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T00:14:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = paint
TEMPLATE = app


SOURCES += main.cpp\
        interfaces.cpp \
        mainWindow.cpp \
        toolBSpline.cpp \
        toolBezierCurve.cpp \
        toolCircle.cpp \
        toolFulfill.cpp \
        toolLine.cpp \
        toolPolygon.cpp \
        tools.cpp

HEADERS  += \
    mainWindow.h \
    toolBSpline.h \
    toolBezierCurve.h \
    toolCircle.h \
    toolFulfill.h \
    toolLine.h \
    toolPolygon.h \
    tools.h

FORMS    += \
    mainWindow.ui
