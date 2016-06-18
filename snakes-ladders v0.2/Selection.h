#ifndef SELECTION_H
#define SELECTION_H

#include "Arrow.h"
#include "Button.h"
#include "Piece.h"
#include "TextBox.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QObject>


class Selection: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Selection(int selPosX, int selPosY, QGraphicsItem * parent = NULL);

    Arrow * arrowL;
    Piece * piece;
    Arrow * arrowR;
    TextBox * textBox;
    Button * lockBtn;
    QGraphicsTextItem * text;
};

#endif // SELECTION_H
