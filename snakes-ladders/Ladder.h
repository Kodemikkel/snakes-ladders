#ifndef LADDER_H
#define LADDER_H


#include <QGraphicsPixmapItem>

class Ladder: public QGraphicsPixmapItem {
public:

// Constructor
    Ladder();

// Public getters


// Public setters


// Public methods
    void makeLadder(int tileA, int tileB);
    void drawLadder(int posX,
                    int posY,
                    int nLadders,
                    int xDir = 0,
                    int yDir = 1,
                    bool vertLad = true,
                    float angle = 0);
    void initLadders();
    void tempInitLad();

// Public members

private:

    // Private members
    int aPosX;
    int aPosY;
    int bPosX;
    int bPosY;
    float lLength;
    float lAng;
    float scale;
    QMap<int, int> ladders;
};

#endif // LADDER_H
