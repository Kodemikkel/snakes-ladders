#include "TextBox.h"
#include "Game.h"
#include <QFontDatabase>

extern Game * game;

TextBox::TextBox(QString textValue, bool editable, QGraphicsItem * parent): QGraphicsRectItem(parent) {
    this->editable = editable;

// Draw the textbox
    setRect(0, 0, 352, 64);
    if(!editable) {
        this->setPen(Qt::NoPen); // Removes border
    } else if(editable) {
// TODO: Fix brush method in gameinfo
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(255, 255, 255, 255));
        setBrush(brush);
    }

// Set font, position and draw text
    text = new QGraphicsTextItem(textValue, this);
    text->setFont(game->info->fontDb->font("Built Titling Rg", 0, 25));
    int xPos = 0;
    int yPos = rect().height() / 2 - text->boundingRect().height() / 2;
    text->setPos(xPos,yPos);
}

QString TextBox::getText() {
    return this->text->toPlainText();
}

bool TextBox::getEditable() {
    return editable;
}

void TextBox::setText(QString text) {
    this->text->setPlainText(text);
}

void TextBox::setEditable(bool edit) {
    if(edit) {
        text->setTextInteractionFlags(Qt::TextEditorInteraction);
        this->editable = true;
    } else {
        text->setTextInteractionFlags(Qt::NoTextInteraction);
        this->editable = false;
    }
}


void TextBox::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if(this->editable) {
        this->text->setTextInteractionFlags(Qt::TextEditorInteraction);
        this->text->setFocus(Qt::MouseFocusReason);
    }
}

