#ifndef GAME_H
#define GAME_H

#include "Tile.h"
#include "GameInfo.h"
#include "Container.h"
#include "Timer.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Dice.h"

class Game: public QGraphicsView {
    Q_OBJECT
public:
// Constructors
    Game(QWidget * parent = NULL);

// Public members
    QGraphicsScene * scene;
    Tile * tile;
    Piece * piece;
    GameInfo * info;
    Container * selContainer;
    Timer * timer;
    Timer * diceTimer;
    Dice * dice;

// Public methods
    void displayMainMenu();

public slots:
    void start();
    void displayPlayerSelect();
    void displayMatchConfig(int players);
    void rollDice();
    void back();

private:
    void drawBoard(int x, int y);
    void drawGUI();
    void drawDice(); //int x, int y, int width, int height
    void createPiece();
    void drawTimer();
};

#endif // GAME_H
