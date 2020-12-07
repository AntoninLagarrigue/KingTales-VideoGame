#include "Monster.h"

#include <QPainter>
#include <QDebug>

Monster::Monster(QGraphicsItem *parent) : QGraphicsItem(parent), direction_(true)
{
    health_ = new Health(25);
    setFlag(ItemClipsToShape);
    sprite_image_ = new QPixmap(":/sprites/monstre.png");
    QTimer *timer = new QTimer(this);
    timer->setInterval(70);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start();

    health_timer_ = new QTimer();
    health_timer_->setInterval(5);
    connect(health_timer_,SIGNAL(timeout()),this,SLOT(die()));
    health_timer_->start();

}

QRectF Monster::boundingRect() const
{
    return QRectF(0,0,78,74);
}



void Monster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(
                boundingRect(),
                *sprite_image_,
                QRectF(current_frame_, 0, 165, 174));

}

void Monster::move()
{

    if ( direction_){
        setTransform(QTransform());
        moveBy(2, 0);
    }
    else {
        setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        moveBy(-2, 0);}

    if (x() > 2920){
        direction_ = false;
    }

    if (x() < 2400){
        direction_ = true;
    }

    //If we touch something a fireball
    QList<QGraphicsItem *> colliding_items = collidingItems();

           for (int i = 0, n = colliding_items.size(); i < n; ++i){
               if (typeid(*(colliding_items[i])) == typeid(FireBall)){
                   qDebug() << " tue par balle" << endl;
                   health_->setHealthNb(health_->getHealthNb() - 5);
                   qDebug() << health_->getHealthNb() << endl;
                   delete colliding_items[i];
                   return;
               }
           }
           nextFrame();
}

void Monster::die()
{
    if (health_->getHealthNb() <= 0){
        delete(this);

    }
}



void Monster::nextFrame() {

    current_frame_ += 192;
    if (current_frame_ >= 1901 )
    {
        current_frame_ = 0;
    }
    this->update();
}

