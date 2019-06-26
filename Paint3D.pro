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
    colordisplay.cpp \
    dialognewcanvas.cpp \
        mainwindow.cpp \
    cutbox.cpp \
    cutellipsoid.cpp \
    cutsphere.cpp \
    cutvoxel.cpp \
    geometricfigure.cpp \
    plotter.cpp \
    plotter3d.cpp \
    putbox.cpp \
    putellipsoid.cpp \
    putsphere.cpp \
    putvoxel.cpp \
    sculptor.cpp

HEADERS  += mainwindow.h \
    colordisplay.h \
    cutbox.h \
    cutellipsoid.h \
    cutsphere.h \
    cutvoxel.h \
    dialognewcanvas.h \
    geometricfigure.h \
    plotter.h \
    plotter3d.h \
    putbox.h \
    putellipsoid.h \
    putsphere.h \
    putvoxel.h \
    sculptor.h

FORMS    += mainwindow.ui \
    dialognewcanvas.ui

RESOURCES += \
    imagem.qrc
