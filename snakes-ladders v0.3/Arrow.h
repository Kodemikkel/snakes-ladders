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
    Arrow(int arrowPosX, int arrowPosY, int direction, QGraphicsItem * parent = NULL);

// Public methods
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
};

#endif // ARROW_H
