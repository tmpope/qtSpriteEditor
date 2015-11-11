#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T18:56:54
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CXXFLAGS += -fopenmp
#LIBS += -lMagick++ -lMagickCore

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteCreator
TEMPLATE = app

INCLUDEPATH += /usr/include/ImageMagick
INCLUDEPATH += ../backend

SOURCES += main.cpp\
        mainwindow.cpp \
    canvaswidget.cpp \
    WriteGIF.cpp \
    ../backend/sprite.cpp

HEADERS  += mainwindow.h \
    canvaswidget.h \
    WriteGIF.h \
    ../backend/sprite.h

FORMS    += mainwindow.ui

RESOURCES += \
    graphics/graphix.qrc

DISTFILES += \

