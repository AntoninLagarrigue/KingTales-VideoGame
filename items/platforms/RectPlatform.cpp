#include "RectPlatform.h"

RectPlatform :: RectPlatform(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    :QGraphicsRectItem(parent), x_(x), y_(y), width_(width), height_(height)
{
    setFlag(ItemClipsToShape);
    QPen pen;
    pen.setColor(Qt::transparent);
    setPen(pen);

    setRect(x_, y_, width_, height_);
}

RectPlatform :: ~RectPlatform(){
    qDebug() << " Plateforme détruite " << endl;
}

qreal RectPlatform::getX() const
{
    return x_;
}

void RectPlatform::setX(const qreal &x)
{
    x_ = x;
}

qreal RectPlatform::getY() const
{
    return y_;
}

void RectPlatform::setY(const qreal &y)
{
    y_ = y;
}

qreal RectPlatform::getWidth()
{
    return width_;
}

qreal RectPlatform::getHeight()
{
    return height_;
}
