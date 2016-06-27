#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Tile: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
// Constructors
    Tile(int posX = 0, int posY = 0, int spriteX = 0, int spriteY = 0, float scaleX = 1, float scaleY = 1, QGraphicsItem * parent = NULL);

// Getters


// Setters


// Public methods
    void drawTileNum(int spriteNum, int posX = 0, int posY = 0, float scaleX = 1, float scaleY = 1);

// Public members


private:
// Private members
};

#endif // TILE_H
