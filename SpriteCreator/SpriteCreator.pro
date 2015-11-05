#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T18:56:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvaswidget.cpp \
    sprite.cpp

HEADERS  += mainwindow.h \
    canvaswidget.h \
    sprite.h

FORMS    += mainwindow.ui
