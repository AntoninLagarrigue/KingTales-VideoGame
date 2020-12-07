#ifndef POTION_H
#define POTION_H

#include <QGraphicsItem>
#include <QPixmap>
#include "Consumable.h"

class Potion : public Consumable {

public :
    Potion(QGraphicsItem * parent = 0);
    ~Potion();
};

#endif // POTION_H
