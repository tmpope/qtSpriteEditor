#-------------------------------------------------
#
# Project created by QtCreator 2015-11-07T18:46:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testWidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvaswidget.cpp \
    sprite.cpp \
    WriteGIF.cpp

HEADERS  += mainwindow.h \
    canvaswidget.h \
    sprite.h \
    WriteGIF.h

FORMS    += mainwindow.ui
