#include "Scene.h"


Scene::Scene(QObject * parent): QGraphicsScene(parent) {
    QImage bkg(":/imgs/background.jpg");
    this->setBackgroundBrush(QBrush(bkg));
}
