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

    void Selection(int nPlayers, int sPiceNo, QGraphicsItem * parent = NULL);

    Arrow * arrowL;
    Piece * piece;
    Arrow * arrowR;
    TextBox * textBox;
    Button * lockBtn;

    void Overview(int ovPlayers, int ovPiceNo, QGraphicsItem * parent = NULL);

    Piece * ovPiece;
    TextBox * ovTextBox;

    bool locked[6] {false, false, false, false, false, false};


public slots:
    void lock(int nPlayer);
    void changePieceL(int nPlayer);
    void changePieceR(int nPlayer);
};

#endif // SELECTION_H
