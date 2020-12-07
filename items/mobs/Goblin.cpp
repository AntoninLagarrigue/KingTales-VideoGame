#include "Goblin.h"

#include <QPainter>
#include <QDebug>

Goblin::Goblin(int x, int y, QGraphicsItem *parent) : x_(x), y_(y), QGraphicsItem(parent), direction_(true)
{
    setPos(x, y);
    health_ = new Health(20);
    setFlag(ItemClipsToShape);
    sprite_image_ = new QPixmap(":/sprites/goblin.webp");
    QTimer *timer = new QTimer(this);
    timer->setInterval(170);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start();

    health_timer_ = new QTimer();
    health_timer_->setInterval(5);
    connect(health_timer_,SIGNAL(timeout()),this,SLOT(die()));
    health_timer_->start();

}

QRectF Goblin::boundingRect() const
{
    return QRectF(0,0,40,45);
}



void Goblin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(
                boundingRect(),
                *sprite_image_,
                QRectF(current_frame_, 0, 35, 53));

}

void Goblin::move()
{

    if ( direction_){
        setTransform(QTransform());
        moveBy(8, 0);
    }
    else {
        setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        moveBy(-8, 0);}

    if (x() > x_ + 150){
        direction_ = false;
    }

    if (x() < x_ - 150){
        direction_ = true;
    }

    //If it touches something a fireball
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

void Goblin::die()
{
    if (health_->getHealthNb() <= 0){
        delete(this);

    }
}



void Goblin::nextFrame() {

    current_frame_ += 64;
    if (current_frame_ >= 446 + 64 )
    {
        current_frame_ = 0;
    }
    this->update();
}

