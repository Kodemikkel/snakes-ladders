#ifndef DICE_H
#define DICE_H

#include "Timer.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QObject>

class Dice: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
// Constructors
    Dice(int diceX, QGraphicsItem * parent = NULL);

// Getters
    int getSprite();
    int getDiceSpriteCount();

// Setters
    void setSprite(int spriteNum);
    void setDiceSpriteCount(int spriteCount);
    void setPos(int posX, int posY);

// Public methods


// Public members


// Events
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

signals:
    void diceClicked();
    void diceRolled();

public slots:
    void rollDice();

private:
// Private members
    int spriteNum;
    int diceSpriteCount = 0;
    Timer * diceTimer;
};

#endif // DICE_H
