#include "Board.h"
#include "Game.h"
#include <QMapIterator>

#include <QDebug>

extern Game * game;

Board::Board(QGraphicsItem * parent): QGraphicsRectItem(parent) {

}

float Board::getScale() {
    return this->scale;
}
int Board::getBoardPosX() {
    return this->boardPosX;
}

int Board::getBoardPosY() {
    return this->boardPosY;
}

void Board::setScale(float scale) {
    this->scale = scale;
}

void Board::setBoardPos(int boardPosX, int boardPosY) {
    this->boardPosX = boardPosX;
    this->boardPosY = boardPosY;
}

void Board::drawBoard(int boardPosX, int boardPosY, float scale) {

// Set all the members to match the parameters
    this->setScale(scale);
    this->setBoardPos(boardPosX, boardPosY);

// Draw 10 x 10 tiles til draw the complete board
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            drawBigTile(boardPosX + j * 3 * 64 * scale,
                        boardPosY + i * 3 * 64 * scale,
                        scale);
        }
    }

}

void Board::drawBigTile(float posX, float posY, float scale) {

// Array with tileNum to tell what texture to use in a tile â 3 x 3 pixmaps
    const int tileArray[3][3] = {
        1, 1, 1,
        1, 1, 1,
        2, 2, 2
    };

    int tileArrayLength = sizeof(tileArray) / sizeof(*tileArray);

// Draw every pixmap in the tile, with shadows and numbers
    for(int y = 0; y < tileArrayLength; y++) {
        for(int x = 0; x < tileArrayLength; x++) {
            tilePosX = posX + 64 * x * scale;
            tilePosY = posY + 64 * y * scale;

            int spriteNum = tileArray[y][x];

// Draw the main pixmap for the corresponding place in the tile
            drawTile(spriteNum, tilePosX, tilePosY, scale);

            if(x % 3 == 0) {

// Left shadow
                tile->addSprite(13);
            }
            if(y % 3 == 0) {

// Top shadow
                tile->addSprite(14);
            }
            if(x % 3 == 2) {

// Right shadow
                tile->addSprite(15);
            }
            if(y % 3 == 2) {

// Bottom shadow
                tile->addSprite(16);
            }

// Top left piece of the tile
            if(x % 3 == 0 && y % 3 == 0) {

// Draw tile number
                tile->addSprite(tileSpriteNum);

// Algorithm to place the right number at the right tile
                tileSpriteNum++;
                if(tileSpriteNum % 16 == 11) {
                    tileSpriteNum = tileSpriteNum + 6;
                }

// Algorithm to store the numbers in tileRef
                if(tileNumType == 0) {
                    this->tileRef.insert(tileNumVal, tile);
                    tileNumVal--;
                    if(tileNumVal % 10 == 0 && (tileNumVal / 10) % 2 == 1) {
                        tileNumVal = tileNumVal - 9;
                        tileNumType = 1;
                    }
                }
                else if(tileNumType == 1) {
                    this->tileRef.insert(tileNumVal, tile);
                    if(tileNumVal % 10 == 0 && (tileNumVal / 10) % 2 == 1) {
                        tileNumVal = tileNumVal - 11;
                        tileNumType = 0;
                    }
                    tileNumVal++;
                }
            }
        }
    }
}

void Board::drawTile(int spriteNum, int posX, int posY, float scale) {

// Draw a tile
    tile = new Tile(spriteNum, posX, posY, scale, this);
}
