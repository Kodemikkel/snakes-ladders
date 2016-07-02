#include "Overlay.h"
#include "Game.h"
#include <QBrush>
#include <QApplication>
#include <QGraphicsTextItem>
#include <QMapIterator>

#include <QDebug>

extern Game * game;

OverlayText::OverlayText(QGraphicsItem * parent): QGraphicsTextItem(parent) {
    setFont(game->info->fontDb->font("Built Titling Rg", 0, 50));
}

void OverlayText::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    emit this->pressed();
}

Overlay::Overlay(QGraphicsItem * parent): QGraphicsRectItem(parent) {
    this->setRect(0, 0, game->width(), game->height());
    this->setBrush(QColor(50, 50, 50, 200));
    this->setPen(Qt::NoPen);

    options.insert(1, "Continue");
    options.insert(2, "Main menu");
    options.insert(3, "Exit");

    QMapIterator<int, QString> i(options);
    while(i.hasNext()) {
        i.next();
        text = new OverlayText(this);
        this->text->setPlainText(i.value());
        this->text->setX(game->width() / 2 - this->text->boundingRect().width() / 2);
        if(options.size() % 2 == 1) {
            this->text->setY((game->height() / 2) -
                       (this->text->boundingRect().height() / 2) +
                       (this->text->boundingRect().height() *
                        (((i.key() -
                           (options.size() -
                            i.key())) - 1) / 2)));
        }
        else {
            this->text->setY((game->height() / 2) -
                       (this->text->boundingRect().height() / 2) +
                       (this->text->boundingRect().height() *
                        (float)(i.key() -
                                (options.size() / 2) - 0.5)));
        }

        switch (i.key()) {
            case 1:
                connect(this->text, SIGNAL(pressed()), this, SLOT(cont()));
                break;
            case 2:
                connect(this->text, SIGNAL(pressed()), this, SLOT(menu()));
                break;
            case 3:
                connect(this->text, SIGNAL(pressed()), this, SLOT(quit()));
                break;
            default:
                connect(this->text, SIGNAL(pressed()), this, SLOT(cont()));
                break;
        }

    }

}

void Overlay::cont() {
    game->timer->pauseTime();
}

void Overlay::menu() {
    game->info->setPause(false);
    game->displayMainMenu();
}

void Overlay::quit() {
    game->close();
}
