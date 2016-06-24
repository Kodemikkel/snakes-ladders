#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Piece: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
// Constructors
    Piece(int piece, int piecePosX, int piecePosY, int pieceScaleX, int pieceScaleY, QGraphicsItem * parent = NULL);


// Getters
    int getPos();
    QString getOwner();

// Setters
    void setOwner(QString player);
    void setPos(int x, int y);

private:
    QString owner;
};

#endif // PIECE_H
