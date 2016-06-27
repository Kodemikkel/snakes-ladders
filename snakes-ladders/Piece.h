#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Piece: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
// Constructors
    Piece(int sprite, int piecePosX, int piecePosY, float pieceScaleX, float pieceScaleY, QGraphicsItem * parent = NULL);

// Getters
    int getPos();
    QString getOwner();
    int getSpriteNum();

// Setters
    void setOwner(QString player);
    void setSpriteNum(int num);

// Public methods

// Public members

private:
// Private members
    QString owner;
    int spriteNum;
    float pieceScaleX;
    float pieceScaleY;
    int piecePosX;
    int piecePosY;
};

#endif // PIECE_H
