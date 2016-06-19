#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "TextBox.h"
#include "Tile.h"

class Game: public QGraphicsView {
    Q_OBJECT
public:
// Constructors
    Game(QWidget * parent = NULL);

// Public methods
    void displayMainMenu();

// Public attributes
    QGraphicsScene* scene;
    Tile* tile;
    Piece* piece;

    int players;

    QMap<QString, TextBox*> textBoxes;

public slots:
    void start();
    void displayPlayerSelect();
    void displayMatchConfig(int players);
    void rollDice();
    void testSlot();
    void back();

private:
    void drawBoard(int x, int y);
    void drawGUI();
    void drawDice(); //int x, int y, int width, int height
    void createPiece();
};

#endif // GAME_H
