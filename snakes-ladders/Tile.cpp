#include "Tile.h"
#include "Game.h"

extern Game* game;
bool setFont = false;

Tile::Tile(int posX, int posY, int spriteX, int spriteY, float scaleX, float scaleY, QGraphicsItem *parent): QGraphicsPixmapItem(parent) {
    QRect rect(spriteX, spriteY, 64, 64);
    QPixmap original(":/imgs/Spritesheet.png");
    QPixmap cropped = original.copy(rect);
    QPixmap scaled = cropped.scaled(QSize(64 * scaleX, 64 * scaleY));
    setOffset(posX, posY);
    setPixmap(scaled);
}

QList<Piece*> Tile::getPieces() {
    return pieces;
}

void Tile::movePiece(int x, int y) {

}

void Tile::drawTileNum(int posX, int posY, int spriteX, int spriteY, float scaleX, float scaleY) {
    QRect rect(spriteX, spriteY, 64, 64);
    QPixmap original(":/imgs/Spritesheet.png");
    QPixmap cropped = original.copy(rect);
    QPixmap scaled = cropped.scaled(QSize(64 * scaleX, 64 * scaleY));
    setOffset(posX, posY);
    setPixmap(scaled);


    //QGraphicsTextItem* tileNum = new QGraphicsTextItem(QString(num));
    //int fontId = QFontDatabase::addApplicationFont(":/fonts/built_titling_bd.ttf");
    //QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    //QFont built(family);
    //tileNum->setFont(built);

    if(setFont == false) {
        setFont = true;
    }
    //tileNum->setPos(txtX, txtY);
    //game->scene->addItem(tileNum);
}
