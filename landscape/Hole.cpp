#include "Hole.h"

Hole::Hole(int width, int height, QGraphicsItem * parent) : width_(width), height_(height), QGraphicsItem(parent)
{
     sprite_image_ = new QPixmap(":/sprites/sea.png");
     setFlag(QGraphicsItem::ItemIsFocusable);
     setFlag(ItemClipsToShape);
     setFocus();

}
Hole::~Hole()
{

}
void Hole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->drawPixmap(
//                boundingRect(),
//                *sprite_image_,
//                QRectF(0, 15, 19, 4));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Hole::boundingRect() const
{
    return QRectF(15, 50, width_, height_);
}
