#-------------------------------------------------
#
# Project created by QtCreator 2019-06-05T07:28:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Paint3D
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cutbox.cpp \
    cutellipsoid.cpp \
    cutsphere.cpp \
    cutvoxel.cpp \
    geometricfigure.cpp \
    putbox.cpp \
    putellipsoid.cpp \
    putsphere.cpp \
    putvoxel.cpp \
    sculptor.cpp \
    plotterxy.cpp

HEADERS  += mainwindow.h \
    cutbox.h \
    cutellipsoid.h \
    cutsphere.h \
    cutvoxel.h \
    geometricfigure.h \
    putbox.h \
    putellipsoid.h \
    putsphere.h \
    putvoxel.h \
    sculptor.h \
    plotterxy.h

FORMS    += mainwindow.ui
