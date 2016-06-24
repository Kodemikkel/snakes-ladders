#ifndef SELECTION_H
#define SELECTION_H

#include "Arrow.h"
#include "Button.h"
#include "Piece.h"
#include "TextBox.h"
#include <QGraphicsRectItem>
#include <QObject>


class Container: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Container(QGraphicsItem * parent = NULL);

    void Selection(int nPlayers, QGraphicsItem * parent = NULL);

    Arrow * arrowL;
    Piece * piece;
    Arrow * arrowR;
    TextBox * textBox;
    Button * lockBtn;

    void Overview(int ovPlayers, QGraphicsItem * parent = NULL);

    Piece * ovPiece;
    TextBox * ovTextBox;
};

#endif // SELECTION_H
