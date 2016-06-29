#ifndef GAMEINFO_H
#define GAMEINFO_H


#include "TextBox.h"
#include <QString>
#include <QStringList>
#include <QMap>
#include <QList>
#include <QFont>
#include <QFontDatabase>
#include "Container.h"
#include "Piece.h"

class GameInfo {
public:
// Constructors
    GameInfo();

// Getters
    QBrush getBrush();
    int getQuotient(int divident, int divisor);
    int getFontNum();
    int getPlayers();
    int getMaxPlayers();
    int getPieceSpriteStart();
    int getPieceAmount();
    bool getPause();

// Setters
    void setPlayers(int players);
    void setMaxPlayers(int maxPlayers);
    void setupBrush(QColor color = QColor(157, 116, 86, 255));
    void setPieceSpriteStart(int pieceStart);
    void setPieceAmount(int pieceAmount);
    void setPause(bool pause);
    QPixmap setSprite(int spriteNum,
                      float scaleX = 1, float scaleY = 1,
                      int spriteW = 64, int spriteH = 64,
                      QString path = ":/imgs/Spritesheet.png");

// Public methods
    void addFont(QString path);
    void drawTitle();
    int randNum(int low, int high);

// Public members
    QGraphicsTextItem * titleText;
    QMap<int, TextBox*> textBoxMap;
    QMap<int, Piece*> piecesMap;
    QMap<int, QGraphicsPixmapItem*> checkmarkMap;
    QFontDatabase * fontDb;
    QStringList names = (QStringList()
        << "Player 1"
        << "Player 2"
        << "Player 3"
        << "Player 4"
        << "Player 5"
        << "Player 6"
        << "Player 7");

    bool locked[6] {false, false, false, false, false, false};

private:
    QBrush brush;
    int fontNum = 1;
    int players;
    int maxPlayers = 6;
    int pieceSpriteStart = 17;
    int pieceAmount = 22;
    bool pause = false;
};

#endif // GAMEINFO_H
