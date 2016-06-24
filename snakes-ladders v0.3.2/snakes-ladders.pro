#-------------------------------------------------
#
# Project created by QtCreator 2016-06-11T00:40:28
#
#-------------------------------------------------

QT       += core gui

win32:RC_ICONS += SL.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snakes-ladders
TEMPLATE = app


SOURCES += main.cpp \
    Button.cpp \
    Game.cpp \
    Piece.cpp \
    Tile.cpp \
    Dice.cpp \
    Arrow.cpp \
    Selection.cpp \
    TextBox.cpp \
    Board.cpp \
    GameInfo.cpp

HEADERS  += \
    Button.h \
    Game.h \
    Piece.h \
    Tile.h \
    Dice.h \
    Arrow.h \
    Selection.h \
    TextBox.h \
    Board.h \
    GameInfo.h

FORMS    +=

RESOURCES += \
    res.qrc
