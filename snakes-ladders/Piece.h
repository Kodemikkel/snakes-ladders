#ifndef PIECE_H
#define PIECE_H

#include "Timer.h"
#include <QGraphicsPixmapItem>
#include <QObject>

class Piece: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:

// Constructors
    Piece(int sprite,
          int posX,
          int posY,
          float scale,
          QGraphicsItem * parent = NULL);

// Getters
    int getPosX();
    int getPosY();
    QString getOwner();
    int getSpriteNum();

// Setters
    void setOwner(QString player);
    void setSpriteNum(int num);

// Public methods
    void addPosX(int addX);
    void addPosY(int addY);

// Public members
    bool forward;
    int finalTileNum;

private:
// Private members
    QString owner;
    int spriteNum;
    float scale;
    int posX;
    int posY;
};

class MoveablePiece: public Piece {
    Q_OBJECT
public:

// Constructors
    MoveablePiece(int sprite,
                  int posX,
                  int posY,
                  float scale,
                  QGraphicsItem *parent);

// Getters
    int getTileNum();
    int getStepsLeft();
    int getStepsToTake();

// Setters
    void setTileNum(int tileNum);
    void setStepsLeft(int stepsLeft);
    void setStepsToTake(int stepsToTake);


public slots:
    void move();
    void initMove(int stepsLeft);
    void climbLadder();

private:

// Private members
    int tileNum;
    int stepsLeft;
    int stepsToTake;
    int endTile;
    Timer * moveTimer;
};

#endif // PIECE_H
