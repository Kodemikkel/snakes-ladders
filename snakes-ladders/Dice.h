#ifndef DICE_H
#define DICE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Dice: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
// Constructors
    Dice(int diceX, QGraphicsItem * parent = NULL);

// Getters
    int getSprite();

// Setters
    void setSprite(int spriteNum);

// Public methods
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

// Public members


private:
// Private members
    int spriteNum;

signals:
    void diceClicked();
};

#endif // DICE_H
