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
         float scaleX = .4375,
         float scaleY = .4375,
         QGraphicsItem * parent = NULL);

// Getters
    int getPosX();
    int getPosY();
    float getScaleX();
    float getScaleY();

// Setters
    void setPosY(int value);
    void setPosX(int value);
    void setScaleX(float value);
    void setScaleY(float value);

// Public methods
    void addSprite(int tileNum);

// Public members

private:
    // Private members
    int posX;
    int posY;
    float scaleX;
    float scaleY;
};

#endif // TILE_H
