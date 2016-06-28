#include "Tile.h"
#include "Game.h"

#include <QDebug>

extern Game * game;

Tile::Tile(int spriteNum,
           int posX,
           int posY,
           float scaleX,
           float scaleY,
           QGraphicsItem * parent):
    QGraphicsPixmapItem(parent) {

    this->setPosX(posX);
    this->setPosY(posY);
    this->setScaleX(scaleX);
    this->setScaleY(scaleY);
    this->setPixmap(game->info->setSprite(spriteNum,
                                          this->getScaleX(),
                                          this->getScaleY()));
    this->setOffset(posX, posY);
}

int Tile::getPosX() {
    return this->posX;
}

int Tile::getPosY() {
    return this->posY;
}

float Tile::getScaleX() {
    return this->scaleX;
}

float Tile::getScaleY() {
    return this->scaleY;
}

void Tile::setPosX(int value) {
    this->posX = value;
}

void Tile::setPosY(int value) {
    this->posY = value;
}

void Tile::setScaleX(float value) {
    this->scaleX = value;
}

void Tile::setScaleY(float value) {
    this->scaleY = value;
}

void Tile::addSprite(int tileNum) {
    Tile * sprite = new Tile(tileNum,
                             this->posX,
                             this->posY,
                             this->scaleX,
                             this->scaleY,
                             this);
    sprite->setPixmap(game->info->setSprite(tileNum,
                                            this->getScaleX(),
                                            this->getScaleY()));
}
