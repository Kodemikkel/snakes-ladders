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

// Getters
    QString getText();

// Setters
    void setText(QString text);

// Public methods

// Public members


// Events
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

signals:
    void clicked();

private:
// Private members
    QGraphicsTextItem * text;
};

#endif // BUTTON_H
