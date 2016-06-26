#ifndef CONTAINER_H
#define CONTAINER_H

#include "Arrow.h"
#include "Button.h"
#include "Piece.h"
#include "TextBox.h"
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsPixmapItem>


class Container: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
// Constructor
    Container(QGraphicsItem * parent = NULL);


    void Selection(int nPlayers, int sPieceNo, QGraphicsItem * parent = NULL);

    Arrow * arrowL;
    Piece * piece;
    Arrow * arrowR;
    TextBox * textBox;
    Button * lockBtn;

    void Overview(int ovPlayers, int ovPieceNo);


    Piece * ovPiece;
    TextBox * ovTextBox;
    QGraphicsPixmapItem * checkmarkRect;

    bool compareSprites(int sprite1, int sprite2);


public slots:
    void lock(int nPlayer);
    void changePieceL(int nPlayer);
    void changePieceR(int nPlayer);
    void checkmark(int nPlayer);
};

#endif // CONTAINER_H
