#include "Tile.h"
#include "Game.h"

#include <QDebug>

extern Game * game;

Tile::Tile(int spriteNum,
           int posX,
           int posY,
           float scale,
           QGraphicsItem * parent):
    QGraphicsPixmapItem(parent) {

    this->setPosX(posX);
    this->setPosY(posY);
    this->setScale(scale);
    QPixmap pixmap = game->info->setSprite(spriteNum,
                                           this->getScale());
    this->setPixmap(pixmap);
    this->setOffset(posX, posY);
}

int Tile::getPosX() {
    return this->posX;
}

int Tile::getPosY() {
    return this->posY;
}

float Tile::getScale() {
    return this->scale;
}

void Tile::setPosX(int value) {
    this->posX = value;
}

void Tile::setPosY(int value) {
    this->posY = value;
}

void Tile::setScale(float value) {
    this->scale = value;
}

void Tile::addSprite(int tileNum) {
    Tile * sprite = new Tile(tileNum,
                             this->posX,
                             this->posY,
                             this->getScale(),
                             this);
    sprite->setPixmap(game->info->setSprite(tileNum,
                                            this->getScale()));
}
