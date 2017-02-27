#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T16:04:01
#
#-------------------------------------------------


QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextAdventureGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    world.cpp \
    stats.cpp \
    attack.cpp

HEADERS  += mainwindow.h \
    world.h \
    stats.h \
    attack.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES +=
