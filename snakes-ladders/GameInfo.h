#ifndef GAMEINFO_H
#define GAMEINFO_H


#include "TextBox.h"
#include <QString>
#include <QStringList>
#include <QMap>
#include <QList>
#include "Container.h"
#include "Piece.h"

class GameInfo {
public:
    GameInfo();
    int players;

    QStringList names = (QStringList()
        << "Player 1"
        << "Player 2"
        << "Player 3"
        << "Player 4"
        << "Player 5"
        << "Player 6"
        << "Player 7");

    QMap<int, QGraphicsTextItem**> textBoxMap;
    QMap<int, Piece**> piecesMap;

    int pieces[6] {0, 1, 2, 3, 4, 5};
};

#endif // GAMEINFO_H
