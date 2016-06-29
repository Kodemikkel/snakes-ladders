#include "Ladder.h"
#include "Game.h"
#include "Tile.h"
#include <math.h>
#include <QtMath>

#include <QDebug>

extern Game * game;

Ladder::Ladder(): QGraphicsPixmapItem(game->board) {

// Call temporary ladder initializing method
    this->tempInitLad();
}

void Ladder::makeLadder(int tileA, int tileB) {
    this->scale = game->board->getScale();
    int xDir, yDir, xLength, yLength, nLadders;
    float lCos;
    bool vertLad = false;

// Sets x and y coordinates for both start and stop tile of ladder
    aPosX = game->board->tileRef[tileA]->getPosX() + (64 * scale);
    aPosY = game->board->tileRef[tileA]->getPosY() + (64 * 1.5 * scale);
    bPosX = game->board->tileRef[tileB]->getPosX() + (64 * scale);
    bPosY = game->board->tileRef[tileB]->getPosY() + (64 * 1.5 * scale);

// Get the difference between the two x-coordinates
    if(aPosX > bPosX) {
        xDir = 0;
        xLength = aPosX - bPosX;
    }
    else if(aPosX < bPosX) {
        xDir = 1;
        xLength = bPosX - aPosX;
    }
    else if(aPosX = bPosX) {
// Detects if it is a vertical ladder
        xLength = NULL;
        vertLad = true;
    }

// Get the difference between the two y-coordinates
    if(aPosY > bPosY) {
        yDir = 0;
        yLength = aPosY - bPosY;
    }
    else if(aPosY < bPosY) {
        yDir = 1;
        yLength = bPosY - aPosY;
    }

    if(!vertLad) {


// Use pythagoras and cosine to get length and angle of ladder
        lLength = sqrt((xLength * xLength) + (yLength * yLength));
        lCos = xLength / lLength;
        lAng = qRadiansToDegrees(qAcos(lCos));

// TODO: Add one ladder when nLadders % 64 > 32

// Get the number of ladder pixmaps needed for the whole ladder
        if(lLength < 64 * (game->board->getScale())) {
            nLadders = game->info->getQuotient(64 * (game->board->getScale()),
                                               lLength);
        }
        else {
            nLadders = game->info->getQuotient(lLength,
                                               64 * (game->board->getScale()));
        }

// Draw the ladder
        this->drawLadder(aPosX, aPosY, nLadders, xDir, yDir, vertLad, lAng);
    }
    else {

// Draw vertical ladder
        nLadders = yLength / (64 * (game->board->getScale()));
        this->drawLadder(aPosX, aPosY, nLadders, xDir, yDir, vertLad);
    }
}

void Ladder::drawLadder(int posX,
                        int posY,
                        int nLadders,
                        int xDir,
                        int yDir,
                        bool vertLad,
                        float angle) {

// Draw a ladder tile for every tile needed to complete a ladder
    for(int l = 0; l < nLadders; l++) {
// Draw the tile
        Tile * tile = new Tile(4 + yDir,
                               posX,
                               posY + (64 * game->board->getScale() * l),
                               game->board->getScale(),
                               game->board->getScale(),
                               game->board);

// Rotate the ladder tile
        tile->setTransformOriginPoint(posX + 32 * this->scale, posY);
        if(xDir == 0 && yDir == 1) {
            tile->setRotation(90 - angle);
        }
        else if(xDir == 0 && yDir == 0) {
            tile->setRotation(90 + angle);
        }
        else if(xDir == 1 && yDir == 0) {
            tile->setRotation(270 - angle);
        }
        else if(xDir == 1 && yDir == 1) {
            tile->setRotation(270 + angle);
        }
        if(vertLad && yDir == 1) {
            tile->setRotation(0);
        }
        else if(vertLad && yDir == 0) {
            tile->setRotation(180);
        }
    }
}

void Ladder::initLadders() {
    int maxLads = game->info->randNum(5, 7);
    int start, stop;
    maxLads = NULL; // Remove this line when next TODO is done

// TODO: Fix random algorithm
    for(int lad = 0; lad < maxLads; lad++) {

    createLadder:

// Get random start tile
        start = game->info->randNum(2, 90);
    stop:

// Get random stop tile
        stop = game->info->randNum(11, 98);
        if(stop == start || start - stop > 50 || stop - start > 50) {
            goto stop;
        }
        else if(game->board->tileRef[start]->getPosY() ==
                game->board->tileRef[stop]->getPosY()) {
            goto stop;
        }

// Check if any of the two tiles are used before
        QMapIterator<int, int> i(ladders);
        while(i.hasNext()) {
            i.next();
            if(i.key() == start || i.key() == stop ||
                    i.value() == start || i.value() == stop) {
                goto createLadder;
            }
        }

// Insert ladders coordinate into a QMap
        this->ladders.insert(start, stop);

// Make ladder
        this->makeLadder(start, stop);
    }


}

void Ladder::tempInitLad() {

// Temporary method to initialize ladders. Remove when initLadders() is fixed

// Insert ladders into QMap ladders
    this->ladders.insert(3, 21);
    this->ladders.insert(8, 30);
    this->ladders.insert(27, 13);
    this->ladders.insert(28, 85);
    this->ladders.insert(52, 29);
    this->ladders.insert(57, 40);
    this->ladders.insert(58, 77);
    this->ladders.insert(62, 22);
    this->ladders.insert(75, 86);
    this->ladders.insert(61, 83);
    this->ladders.insert(88, 18);
    this->ladders.insert(90, 92);
    this->ladders.insert(95, 51);
    this->ladders.insert(97, 78);

// Call makeLadder() for every ladder in QMap ladders
    QMapIterator<int, int> i(ladders);
    while(i.hasNext()) {
        i.next();
        this->makeLadder(i.key(), i.value());
    }
}
