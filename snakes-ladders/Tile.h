#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Tile: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
// Constructors
    Tile(int spriteNum,
         int posX = 0,
         int posY = 0,
         float scale = .4375,
         QGraphicsItem * parent = NULL);

// Getters
    int getPosX();
    int getPosY();
    float getScale();

// Setters
    void setPosY(int value);
    void setPosX(int value);
    void setScale(float value);

// Public methods
    void addSprite(int tileNum);

// Public members

private:
    // Private members
    int posX;
    int posY;
    float scale;
};

#endif // TILE_H
