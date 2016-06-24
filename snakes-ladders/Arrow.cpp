#include "Arrow.h"
#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QApplication>

#include <QDebug>
extern Game * game;

Arrow::Arrow(int arrowPosX, int arrowPosY, int direction, QGraphicsItem * parent): QGraphicsPixmapItem(parent) {
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
}

void Arrow::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    emit arrowClick();
}

void Arrow::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    setOffset(offset().x() , offset().y() + 4);
    QApplication::setOverrideCursor(Qt::PointingHandCursor);

}

void Arrow::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    setOffset(offset().x() , offset().y() - 4);
    QApplication::setOverrideCursor(Qt::ArrowCursor);

}
