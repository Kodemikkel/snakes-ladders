#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsRectItem>

class Board: public QGraphicsRectItem {
public:
    Board(int boardType = 1, int boardPosX = 0, int boardPosY = 0, float scaleX = 1, float scaleY = 1, QGraphicsItem * parent = NULL);

    void drawBoard();

    float scaleX;
    float scaleY;
    float tileNumScaleX;
    float tileNumScaleY;
    int boardPosX;
    int boardPosY;
    int boardType;

    int spriteX[3];
    int spriteY;

};

#endif // BOARD_H
