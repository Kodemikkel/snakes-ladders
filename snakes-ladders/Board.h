#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Tile.h"
#include <QGraphicsRectItem>
#include <QMap>

class Board: public QGraphicsRectItem {
public:
// Constructors
    Board(QGraphicsItem * parent = NULL);

// Getters
    float getScale();
    int getBoardPosX();
    int getBoardPosY();

// Setters
    void setScale(float scale);
    void setScaleY(float scaleY);
    void setBoardPos(int boardPosX, int boardPosY);

// Public methods
    void drawBoard(int boardPosX = 0, int boardPosY = 0, float scale = 1);

// Public members
    QMap<int, Tile*> tileRef;
    QMap<int, MoveablePiece*> players;

private:

// Private methods
    void drawBigTile(int posX, int posY, float scale = 1);
    void drawTile(int spriteNum, int spriteX, int spriteY, float scale = 0.4375);

// Private members
    Tile * tile;
    float scale;
    int boardPosX;
    int boardPosY;
    int tileSpriteX;
    int tileSpriteY;
    int tileNumType = 0;
    int tileSpriteNum = 49;
    int tileNumVal = 100;

};

#endif // BOARD_H
