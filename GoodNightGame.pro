#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T17:44:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoodNightGame
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    observer.cpp \
    subjectofobservation.cpp \
    dice.cpp \
    diceexception.cpp

HEADERS  += mainwindow.h \
    color.h \
    game.h \
    observer.h \
    subjectofobservation.h \
    gamestate.h \
    dice.h \
    diceexception.h
