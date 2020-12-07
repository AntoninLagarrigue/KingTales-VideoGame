#include "Player.h"

#include <QDebug>

Player::Player(QGraphicsItem * parent) : QGraphicsItem(parent)
{
    sprite_image_ = new QPixmap(":/sprites/characters.png");
    is_Left_ = false;
    state_ = 0;
    health_ = new Health(15);
    health_->display();

    current_frame_ = 9;

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(ItemClipsToShape);
    setFocus();

}

QGraphicsItem *Player::getTouchedPlatform()
{
    return touchedPlatform_;
}

void Player::setTouchedPlatform(QGraphicsItem *item)
{
    touchedPlatform_ = item;
}



FireBall * Player::throwFireball()
{
    FireBall * fireball = new FireBall(state_, is_Left_);

    if(state_ < 0)
        fireball->setPos(x() - 23, y() + 12);
    else if (state_ >= 0)
        fireball->setPos(x(), y() + 12);

    return fireball;
}

bool Player::isTouchingFeet(QGraphicsItem *item)
{
    if(!is_Left_  ){
        QRectF feetRect(x(), (y() + boundingRect().height() - 5), boundingRect().width() - 5,5);
        QRectF platformRect(item->boundingRect().x(), item->boundingRect().y(), item->boundingRect().width(), item->boundingRect().height());
        return mapRectToScene(feetRect).intersects(mapRectToScene(platformRect));
    }else{
        QRectF feetRect(x() + 5 , (y() + boundingRect().height() - 5), boundingRect().width() - 5,5);
        QRectF platformRect(item->boundingRect().x(), item->boundingRect().y(), item->boundingRect().width(), item->boundingRect().height());
        return mapRectToScene(feetRect).intersects(mapRectToScene(platformRect));
    }


}

bool Player::isTouchingHead(QGraphicsItem *item)
{
    if(!is_Left_){
        QRectF headRect(x()  , y(), boundingRect().width() -5 , 5);
        QRectF platformRect(item->boundingRect().x(), item->boundingRect().y(), item->boundingRect().width(), item->boundingRect().height());
        return mapRectToScene(headRect).intersects(mapRectToScene(platformRect));

    }else{
        QRectF headRect(x() +5 , y(), boundingRect().width()  , 5);
        QRectF platformRect(item->boundingRect().x(), item->boundingRect().y(), item->boundingRect().width(), item->boundingRect().height());
        return mapRectToScene(headRect).intersects(mapRectToScene(platformRect));

    }

}

bool Player::isTouchingPlatform(QGraphicsItem *item)
{
    QRectF playerRect(x(), (y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF platformRect(item->boundingRect().x(), item->boundingRect().y(), item->boundingRect().width(), item->boundingRect().height());
    return playerRect.intersects(platformRect);
}

int Player::getState() const
{
    return state_;
}

void Player::setState(int state)
{
    if (state_ == state) state_ = state;

    else state_ += state;

    if ( state_ != 0){
        if ( state_ == -1)

            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else
            setTransform(QTransform());
    }


}

bool Player::getIs_Left()
{
    return is_Left_;
}

void Player::setIs_Left(bool orientation)
{
    is_Left_ = orientation;
}


void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(
                boundingRect(),
                *sprite_image_,
                QRectF(current_frame_, 32, 23, 32));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Player::nextFrame()
{
    current_frame_ += 32;
    if (current_frame_ > 128)
    {
        current_frame_ = 9;
    }
    this->update();
}


