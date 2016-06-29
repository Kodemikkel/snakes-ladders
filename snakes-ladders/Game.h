#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Button.h"
#include "Container.h"
#include "Dice.h"
#include "GameInfo.h"
#include "Tile.h"
#include "Timer.h"
#include <QGraphicsView>
#include <QSignalMapper>


class Game: public QGraphicsView {
    Q_OBJECT
public:
// Constructors
    Game();

// Public members
    QGraphicsScene * scene;
    GameInfo * info;
    Button * pauseButton;
    MoveablePiece * player;
    Board * board;
    Dice * dice;
    int yFactor = 0;

// Public methods
    void displayMainMenu();
    void spawnPiece();

public slots:
    void start();
    void displayPlayerSelect();
    void displayMatchConfig(int players);
    void back();

private:
    void drawBoard(int x, int y);
    void drawGUI();
    void drawDice();
    void drawTimer();
    void drawPlayerList();

    Piece * piece;
    Container * selectionMenu;
    Timer * timer;
    Button * playButton;
    Button * tutButton;
    Button * optionsButton;
    Button * quitButton;
    Button * playerButton;
    Button * backButton;
    Button * startButton;
    QSignalMapper * signalMapper;
    QGraphicsRectItem * playerListBox;
};

#endif // GAME_H
