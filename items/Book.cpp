#include "Book.h"

#include <QPainter>
#include <QDebug>


Book::Book(QGraphicsItem * parent) : Consumable(parent)
{
    sprite_image_ = new QPixmap(":/sprites/ammoBook.png");
}

Book::~Book(){

}
