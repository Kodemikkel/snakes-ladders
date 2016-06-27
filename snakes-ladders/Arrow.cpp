#include "Arrow.h"
#include "Game.h"
#include <QApplication>
#include <QGraphicsRectItem>

extern Game * game;

Arrow::Arrow(int arrowPosX, int arrowPosY, int direction, bool clickable, QGraphicsItem * parent): QGraphicsPixmapItem(parent) {

// Choose sprite depending on orientation
    if(direction == 0) {
        this->spriteNum = 11;
    }
    else if (direction == 1) {
        this->spriteNum = 12;
    }

// Set position and draw the piece
    this->setPixmap(game->info->setSprite(this->spriteNum));
    this->setOffset(arrowPosX, arrowPosY);

// Allow responding to hovering events
    setAcceptHoverEvents(true);

// Set the clickable member to whatever is passed to the constructor (true/false)
// This will enable or disable the click events
    setClickable(clickable);
}

void Arrow::setClickable(bool clickable) {
    this->clickable = clickable;
}

void Arrow::mousePressEvent(QGraphicsSceneMouseEvent * event) {
// Check if the object should be clickable or not
    if(this->clickable) {
        emit arrowClick();
    }
}

void Arrow::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
// Check if the object should be clickable or not
    if(this->clickable) {
        this->setOffset(offset().x() , offset().y() + 4);
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
    }

}

void Arrow::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
// Check if the object should be clickable or not
    if(this->clickable) {
        this->setOffset(offset().x() , offset().y() - 4);
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    }

}
