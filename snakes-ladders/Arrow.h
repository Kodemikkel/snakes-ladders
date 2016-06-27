#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class Arrow: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
// Constructors
    Arrow(int arrowPosX, int arrowPosY, int direction, bool clickable, QGraphicsItem * parent = NULL);

// Getters
    bool getClickable();

// Setters
    void setClickable(bool clickable);

// Public methods


// Public members
    int spriteNum;

// Events
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

signals:
    void arrowClick();

private:
// Private members
    bool clickable;
};

#endif // ARROW_H
