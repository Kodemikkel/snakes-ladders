#include "Board.h"
#include "Game.h"

extern Game * game;

Board::Board(QGraphicsItem * parent): QGraphicsRectItem(parent) {

}

float Board::getScaleX() {
    return this->scaleX;
}

float Board::getScaleY() {
    return this->scaleY;
}

float Board::getTileNumScaleX() {
    return this->tileNumScaleX;
}

float Board::getTileNumScaleY() {
    return this->tileNumScaleY;
}

int Board::getBoardPosX() {
    return this->boardPosX;
}

int Board::getBoardPosY() {
    return this->boardPosY;
}

int Board::getBoardType() {
    return this->boardType;
}

void Board::setScaleX(float scaleX) {
    this->scaleX = scaleX;
}

void Board::setScaleY(float scaleY) {
    this->scaleY = scaleY;
}

void Board::setTileNumScaleX(float tileNumScaleX) {
    this->tileNumScaleX = tileNumScaleX;
}

void Board::setTileNumScaleY(float tileNumScaleY) {
    this->tileNumScaleY = tileNumScaleY;
}

void Board::setBoardPosX(int boardPosX) {
    this->boardPosX = boardPosX;
}

void Board::setBoardPosY(int boardPosY) {
    this->boardPosY = boardPosY;
}

void Board::setBoardType(int boardType) {
    this->boardType = boardType;
}

void Board::drawBoard(int boardType, int boardPosX, int boardPosY, float scaleX, float scaleY) {
// Set all the members to match the parameters
    this->setScaleX(scaleX);
    this->setScaleY(scaleY);
    this->setTileNumScaleX(scaleX * 1);
    this->setTileNumScaleY(scaleY * 1);
    this->setBoardPosX(boardPosX);
    this->setBoardPosY(boardPosY);
    this->setBoardType(boardType);

// Array to map the board. Which tile goes where?
// TODO: Fix tileArray - make it simpler (3x3)
    const int tileArray[30][30] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
        };

// What board type has been chosen?
    if(this->boardType == 1) {

        int tileNumVal = 100;

        for(int i = 0; i < 30; i++) {
            for(int j = 0; j < 30; j++) {

// SpriteX[0] = tile
// SpriteX[1] = shadow top/bottom
// SpriteX[2] = shadow left/right
                switch(tileArray[i][j]) {
                    case 0: // Air
                        this->spriteX[0] = {0};
                        this->spriteX[1] = {832};
                        this->spriteX[2] = {NULL};
                        break;
                    case 1: // Air
                        this->spriteX[0] = {0};
                        this->spriteX[1] = {NULL};
                        this->spriteX[2] = {NULL};
                        break;
                    case 2: // Dirt
                        this->spriteX[0] = {64};
                        this->spriteX[1] = {960};
                        this->spriteX[2] = {NULL};
                        break;
                }
                if(j % 3 == 0) {
                    this->spriteX[2] = 768;
                }
                if(j % 3 == 2) {
                    this->spriteX[2] = 896;
                }

// Create the tile object with the specified properties, and add it to the scene
                for(int k = 0; k < sizeof(spriteX)/sizeof(*spriteX); k++) {
                    if(this->spriteX[k] != NULL || k == 0) {
                        Tile * tile = new Tile(this->scaleX * 64 * j + this->boardPosX,
                                               this->scaleY * 64 * i + this->boardPosY,
                                               this->spriteX[k], this->spriteY,
                                               this->scaleX, this->scaleY, this);

                        if(j % 3 == 0 && spriteX[k] == 832) {
                            tile->drawTileNum(tileSpriteNum,
                                              this->scaleX * 64 * j + this->boardPosX,
                                              this->scaleY * 64 * i + this->boardPosY,
                                              this->tileNumScaleX, this->tileNumScaleY);

                            tileSpriteNum++;

                            if(tileSpriteNum % 16 == 11) {
                                tileSpriteNum = tileSpriteNum + 6;
                            }
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
        }
    }
}
