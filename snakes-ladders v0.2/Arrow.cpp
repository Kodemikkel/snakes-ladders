#include "Arrow.h"
#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

#include <QDebug>
extern Game * game;

Arrow::Arrow(int direction, QGraphicsItem * parent): QGraphicsPixmapItem(parent) {
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
    setPixmap(scaled);
    qDebug() << "Arrow";
}
