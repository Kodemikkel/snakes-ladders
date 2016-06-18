#ifndef ARROW_H
#define ARROW_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Arrow: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
// Constructors
    Arrow(int direction, QGraphicsItem * parent = NULL);

};

#endif // ARROW_H
