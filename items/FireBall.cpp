#include "FireBall.h"
#include <QTimer>

//#include <QPen>

#include <QDebug>
#include <QMediaPlayer>

FireBall::FireBall(int direction, bool is_left, QGraphicsItem * parent)
    : QObject(), QGraphicsPixmapItem(parent), direction_(direction), is_left_(is_left)
{
//    QMediaPlayer * sound = new QMediaPlayer();
//    sound->setMedia(QUrl(":/sounds/Fireball.mp3"));
//    sound->play();

    setFlag(ItemClipsToShape);

    if (direction_ <= 0 && is_left){
        setPixmap(QPixmap(":/sprites/leftFireball.png"));}


    else {
        setPixmap(QPixmap(":/sprites/rightFireball.png"));
        }

    fireballTimer_ = new QTimer();
    fireballTimer_->connect(fireballTimer_, SIGNAL(timeout()), this, SLOT(move()));
    fireballTimer_->start(50);


}

FireBall::~FireBall()
{

    qDebug() << "on delete la firebal" <<  this->x() << endl;
}

bool FireBall::handleCollisions()
{
    QList<QGraphicsItem*> items =  collidingItems();
    for (int i = 0 ; i < items.size(); i++) {
        if ( typeid (*(items[i])) == typeid (RectPlatform)){
            qDebug() <<  "BOUM" << endl;
            delete this;
            return true;
        }
    }
    return false;
}


void FireBall::move()
{
    if (x() > SCENE_WIDTH - 10 || x() <= 0){
        qDebug() << x() << endl;
        delete this;
        return;
    }

    if(handleCollisions()) return;

    if (direction_ <= 0 && is_left_) {
        moveBy(-17, 0);
    }
    else {
        moveBy(17, 0);
    }

}


