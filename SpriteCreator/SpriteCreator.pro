#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T18:56:54
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvaswidget.cpp \
    sprite.cpp \
    WriteGIF.cpp

HEADERS  += mainwindow.h \
    canvaswidget.h \
    WriteGIF.h \
    sprite.h

FORMS    += mainwindow.ui
