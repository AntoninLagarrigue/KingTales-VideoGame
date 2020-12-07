#include "Potion.h"
#include <QPainter>
#include <QDebug>


Potion::Potion(QGraphicsItem * parent) : Consumable(parent)
{
    sprite_image_ = new QPixmap(":/sprites/healthPotion.png");
}

Potion::~Potion(){

}
