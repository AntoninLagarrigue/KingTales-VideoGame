#ifndef SCENE_H
#define SCENE_H

#include <QDebug>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QPixmap>


#include "Health.h"
#include "Player.h"
#include "RectPlatform.h"
#include "Platform.h"
#include "ground.h"
#include "Potion.h"
#include "Ammo.h"
#include "Book.h"
#include "Hole.h"
#include "Monster.h"
#include "Goblin.h"

#define SCENE_WIDTH 3000
#define SCENE_HEIGHT 400

#define SCENE_GROUND_HEIGHT 368

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject *parent = nullptr);

    //draw
    void drawBackground(QPainter * painter, const QRectF &rect);

    //Getters & Setters
    Player * getPlayer(){ return player_;};
    Health * getHealth(){ return health_;};
    Ammo * getAmmo(){ return ammo_;};
    Monster *getMonster() {return monster_;};

    // Collisions
    QGraphicsItem* collidingPlatforms();
    QGraphicsItem* collidingConsumable();
    bool handleCollisionWithRectItems();
    bool checkCollisionConsumable();
    QGraphicsItem * checkIfTheFloorIsHole();
    bool handleCollisionWithHole();


private:
    // Draw
    //QPixmap * sprite_image_;
    QImage * background_image_;

    // State
    bool is_running_;

    // Items
    Player * player_;
    Monster * monster_;
    Health * health_;
    QList < Goblin *> goblins_;
    Ammo * ammo_;
    QList < RectPlatform *> rectplatforms_;
    QList <Platform*> platforms_;
    Ground * ground;
    QList <Potion*> potions_;
    QList <Book*> books_;
    QList <Hole *> holes_;

};

#endif // SCENE_H
