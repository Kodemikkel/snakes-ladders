#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Button.h"
#include "Container.h"
#include "Dice.h"
#include "GameInfo.h"
#include "Ladder.h"
#include "Scene.h"
#include "Tile.h"
#include "Timer.h"
#include <QGraphicsView>
#include <QSignalMapper>


class Game: public QGraphicsView {
    Q_OBJECT
public:
// Constructors
    Game();

// Public methods
    void displayMainMenu();
    void spawnPiece();

// Public members
    Board * board;
    Scene * scene;
    GameInfo * info;
    Button * pauseButton;
    MoveablePiece * player;
    Dice * dice;
    Ladder * ladder;
    TextBox * playersTurn;
    Timer * timer;

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
