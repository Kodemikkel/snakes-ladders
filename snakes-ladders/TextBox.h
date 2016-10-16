#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QTextCursor>

class TextBox: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
// Constructors
    TextBox(QString textValue, bool editable, QGraphicsItem * parent=NULL);

// Getters
    QString getText();
    bool getEditable();

// Setters
    void setText(QString text);
    void setEditable(bool edit);

// Public methods
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

// Public members

private:
// Private members
    bool editable;
    QGraphicsTextItem * text;
    QString test = "Lol";
};

#endif // TEXTBOX_H
