#ifndef AMMO_H
#define AMMO_H


#include <QGraphicsTextItem>

class Ammo : public QGraphicsTextItem{

 public:
    Ammo(QGraphicsItem * parent = 0);
    ~Ammo();
    int getAmmoNb();
    void setAmmoNb( int ammoNb) ;
    void increaseAmmo(int ammoNb);
    void decreaseAmmo(int ammoNb);

 private :
    int ammoNb_;


};


#endif // AMMO_H
