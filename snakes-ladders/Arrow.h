#ifndef ARROW_H
#define ARROW_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Arrow: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
// Constructors
    Arrow(int arrowPosX, int arrowPosY, int direction, bool clickable, QGraphicsItem * parent = NULL);

// Getters
    bool getClickable();

// Setters
    void setClickable(bool clickSensitive);

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
