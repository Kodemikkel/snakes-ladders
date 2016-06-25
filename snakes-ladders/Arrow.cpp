#include "Arrow.h"
#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QApplication>

#include <QDebug>
extern Game * game;

Arrow::Arrow(int arrowPosX, int arrowPosY, int direction, bool clickable, QGraphicsItem * parent): QGraphicsPixmapItem(parent) {

    int arrowX;

    // Draw the piece
    if(direction == 0) {
        arrowX = 640;
    }
    else if (direction == 1) {
        arrowX = 704;
    }

    QRect arrowRect(arrowX, 0, 64, 64);
    QPixmap original(":/imgs/Spritesheet.png");
    QPixmap cropped = original.copy(arrowRect);
    QPixmap scaled = cropped.scaled(QSize(64 * 1, 64 * 1));
    setOffset(arrowPosX, arrowPosY);
    setPixmap(scaled);

// Allow responding to hovering events
    setAcceptHoverEvents(true);

// Set the clickable member to whatever is passed to the constructor (true/false)
// This will enable or disable the click events
    setClickable(clickable);
}

void Arrow::setClickable(bool clickSensitive) {
// TODO: Create a cleaner way to toggle whether or not the button should be clickable
    clickable = clickSensitive;
}

void Arrow::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if(clickable) {
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        emit arrowClick();
    }
}

void Arrow::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    if(clickable) {
        setOffset(offset().x() , offset().y() + 4);
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
    }

}

void Arrow::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    if(clickable) {
        setOffset(offset().x() , offset().y() - 4);
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    }

}
