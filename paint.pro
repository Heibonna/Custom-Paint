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
        colorPresentation.cpp \
        interfaces.cpp \
        layer.cpp \
        mainWindow.cpp \
        morfology.cpp \
        toolBSpline.cpp \
        toolBezierCurve.cpp \
        toolCircle.cpp \
        toolFulfill.cpp \
        toolFulfilledPolygon.cpp \
        toolLine.cpp \
        toolPolygon.cpp \
        tools.cpp \
        transformations.cpp

HEADERS  += \
    colorPresentation.h \
    layer.h \
    mainWindow.h \
    morfology.h \
    structures.h \
    toolBSpline.h \
    toolBezierCurve.h \
    toolCircle.h \
    toolFulfill.h \
    toolFulfilledPolygon.h \
    toolLine.h \
    toolPolygon.h \
    tools.h \
    transformations.h

FORMS    += \
    mainWindow.ui

RESOURCES += resources.qrc
