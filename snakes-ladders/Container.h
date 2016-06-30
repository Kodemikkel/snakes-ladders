#ifndef CONTAINER_H
#define CONTAINER_H

#include "Arrow.h"
#include "Button.h"
#include "Piece.h"
#include "TextBox.h"
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QSignalMapper>


class Container: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
// Constructor
    Container(int w, int h, QGraphicsItem * parent = NULL);

// Getters

// Setters

// Public methods
    void Selection(int nPlayers, int sPieceNo, QGraphicsItem * parent = NULL);
    void Overview(int ovPlayers, int ovPieceNo);
    void checkmark();
    bool compareSprites(int sprite1, int sprite2);

// Public members
    Piece * piece;
    TextBox * pNameTextBox;
    QMap<int, QGraphicsItem*> objects;

public slots:
    void lock(int nPlayer);
    void changePieceL(int nPlayer);
    void changePieceR(int nPlayer);

private:
// Private members
    QSignalMapper * subPieceMapper;
    QSignalMapper * addPieceMapper;
    QSignalMapper * lockMapper;
    Arrow * arrowL;
    Arrow * arrowR;
    Button * lockBtn;
    QGraphicsPixmapItem * checkmarkRect;
    Piece * ovPiece;
    TextBox * ovTextBox;
    QGraphicsPixmapItem * checkMark;
};

#endif // CONTAINER_H
