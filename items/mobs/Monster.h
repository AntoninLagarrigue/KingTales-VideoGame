#ifndef MONSTER_H
#define MONSTER_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <typeinfo>
#include <QGraphicsScene>

#include <Health.h>
#include <FireBall.h>

class Monster :  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Monster(QGraphicsItem *parent=0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void nextFrame();

public slots:
    void move();

private slots:
    void die();

signals:


private:
    Health * health_;

    //Draw
    QPixmap * sprite_image_;
    int current_frame_;

    //Movement
    bool direction_;

    QTimer * health_timer_;

};
#endif // MONSTER_H
