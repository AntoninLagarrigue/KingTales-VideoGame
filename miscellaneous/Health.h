#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health : public QGraphicsTextItem{

 public:
    Health(int max, QGraphicsItem * parent = 0);
    ~Health();
    int getHealthNb();
    void setHealthNb( int healthNb) ;
    void increaseHealth(int healthNb);
    void display();

 private :
    int healthNb_;
    int healthMax_;


};

#endif // HEALTH_H
