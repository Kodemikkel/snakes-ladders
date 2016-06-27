#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <QGraphicsRectItem>
#include <QMap>

class Board: public QGraphicsRectItem {
public:
// Constructors
    Board(QGraphicsItem * parent = NULL);

// Getters
    float getScaleX();
    float getScaleY();
    float getTileNumScaleX();
    float getTileNumScaleY();
    int getBoardPosX();
    int getBoardPosY();
    int getBoardType();

// Setters
    void setScaleX(float scaleX);
    void setScaleY(float scaleY);
    void setTileNumScaleX(float tileNumScaleX);
    void setTileNumScaleY(float tileNumScaleY);
    void setBoardPosX(int boardPosX);
    void setBoardPosY(int boardPosY);
    void setBoardType(int boardType);

// Public methods
    void drawBoard(int boardType = 1, int boardPosX = 0, int boardPosY = 0, float scaleX = 1, float scaleY = 1);

// Public members
    QMap<int, Tile*> tileRef;

private:
// Private members
    float scaleX;
    float scaleY;
    float tileNumScaleX;
    float tileNumScaleY;
    int boardPosX;
    int boardPosY;
    int boardType;
    int tileNumType = 0;

    int spriteX[3];
    int spriteY = 0;
    int tileSpriteNum = 49;

};

#endif // BOARD_H
