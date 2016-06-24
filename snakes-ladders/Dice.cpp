#include "Dice.h"
#include <stdlib.h> // rand() -> really large int
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include "Game.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

extern Game * game;
Dice::Dice(int diceX, QGraphicsItem * parent): QGraphicsPixmapItem(parent) {

    // Draw the dice
    QRect diceRect(diceX, 896, 128, 128);
    QPixmap original(":/imgs/Spritesheet.png");
    QPixmap cropped = original.copy(diceRect);
    QPixmap scaled = cropped.scaled(QSize(128 * 1, 128 * 1));
    setOffset(900, 742);
    setPixmap(scaled);

}

void Dice::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit diceClicked();
}
