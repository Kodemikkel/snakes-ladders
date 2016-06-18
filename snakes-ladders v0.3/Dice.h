#ifndef DICE_H
#define DICE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Dice: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Dice(int diceX, QGraphicsItem * parent = NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    diceClicked();
};

#endif // DICE_H
