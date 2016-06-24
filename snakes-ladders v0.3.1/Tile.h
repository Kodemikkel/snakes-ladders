#ifndef TILE_H
#define TILE_H

#include <QList>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QFont>
#include <QFontDatabase>
#include "Piece.h"
#include <QObject>

class Tile: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
// Constructors
    Tile(int posX = 0, int posY = 0, int spriteX = 0, int spriteY = 0, float scaleX = 1, float scaleY = 1, QGraphicsItem * parent = NULL);

// Getters/Setters
    QList<Piece*> getPieces();

// Public methods
    void movePiece(int x, int y);
    void drawTileNum(int posX = 0, int posY = 0, int spriteX = 0, int spriteY = 0, float scaleX = 1, float scaleY = 1);

// Public attributes


private:
// Private attributes
    QList<Piece*> pieces;
};

#endif // TILE_H
