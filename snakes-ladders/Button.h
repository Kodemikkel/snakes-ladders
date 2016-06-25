#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class Button: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
// Constructors
    Button(QString name, int w, int h, QGraphicsItem * parent = NULL);

// Public methods
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    QGraphicsTextItem * text;
signals:
    void clicked();

private:
};

#endif // BUTTON_H
