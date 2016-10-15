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
    int getBoardWidth();
    int getBoardHeight();

// Setters
    void setScale(float scale);
    void setScaleY(float scaleY);
    void setBoardPos(int boardPosX, int boardPosY);
    void setBoardWidth(int width);
    void setBoardHeight(int height);

// Public methods
    void drawBoard(int boardPosX = 0, int boardPosY = 0, float scale = 1);

// Public members
    QMap<int, Tile*> tileRef;
    QMap<int, MoveablePiece*> players;

private:

// Private methods
    void drawBigTile(float posX, float posY, float scale = 1);
    void drawTile(int spriteNum, int posX, int posY, float scale = 0.4375);

// Private members
    Tile * tile;
    float scale;
    int boardPosX;
    int boardPosY;
    int tilePosX;
    int tilePosY;
    int tileNumType = 0;
    int tileSpriteNum = 49;
    int tileNumVal = 100;
    int height = 0;
    int width = 0;
    int widthCount = 0;

};

#endif // BOARD_H
