#include "Tile.h"
#include "Game.h"

extern Game* game;
bool setFont = false;

Tile::Tile(int posX, int posY, int spriteX, int spriteY, float scaleX, float scaleY, QGraphicsItem *parent): QGraphicsPixmapItem(parent) {
// TODO: Fix setSprite
    QRect rect(spriteX, spriteY, 64, 64);
    QPixmap original(":/imgs/Spritesheet.png");
    QPixmap cropped = original.copy(rect);
    QPixmap scaled = cropped.scaled(QSize(64 * scaleX, 64 * scaleY));
    setOffset(posX, posY);
    setPixmap(scaled);
}

void Tile::drawTileNum(int spriteNum, int posX, int posY, float scaleX, float scaleY) {
    this->setPixmap(game->info->setSprite(spriteNum, scaleX, scaleY));
    this->setOffset(posX, posY);
}
