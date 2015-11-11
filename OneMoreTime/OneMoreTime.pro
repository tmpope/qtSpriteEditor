#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T17:52:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OneMoreTime
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvaswidget.cpp \
    WriteGIF.cpp \
    sprite.cpp

HEADERS  += mainwindow.h \
    canvaswidget.h \
    WriteGIF.h \
    sprite.h

FORMS    += mainwindow.ui
