#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QColor>
#include <QApplication>


Button::Button(QString name, int w, int h, QGraphicsItem *parent): QGraphicsRectItem(parent) {
// Draw the button
    setRect(0,0,w,h);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(157, 116, 86, 255));
    setBrush(brush);

// Draw the text
    text = new QGraphicsTextItem(name, this);
    int xPos = rect().width() / 2 - text->boundingRect().width() / 2;
    int yPos = rect().height() / 2 - text->boundingRect().height() / 2;
    text->setPos(xPos,yPos);

// Allow responding to hovering events
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    emit clicked();
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(212, 158, 113, 255));
    setBrush(brush);
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(157, 116, 86, 255));
    setBrush(brush);
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}
