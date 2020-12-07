#include "Scene.h"



Scene::Scene(QObject *parent)
    :QGraphicsScene(parent)
{
    //clear();
    background_image_ = new QImage(":/sprites/map.png");

    // Set the scene
    setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);

    // Create & add holes
    Hole * hole1 = new Hole(102, 200);

    Hole * hole2 = new Hole(102, 200);
    Hole * hole3 = new Hole(102, 200);
    Hole * hole4 = new Hole(102, 200);
    Hole * hole5 = new Hole(102, 200);
    Hole * hole6 = new Hole(102, 200);

    hole1->setPos(482, SCENE_GROUND_HEIGHT - 60);

    hole2->setPos(1871, SCENE_GROUND_HEIGHT - 60);
    hole3->setPos(1961, SCENE_GROUND_HEIGHT - 60);
    hole4->setPos(2051, SCENE_GROUND_HEIGHT - 60);
    hole5->setPos(2141, SCENE_GROUND_HEIGHT - 60);
    hole6->setPos(2234, SCENE_GROUND_HEIGHT - 60);


    holes_.push_back(hole1);

    holes_.push_back(hole2);
    holes_.push_back(hole3);
    holes_.push_back(hole4);
    holes_.push_back(hole5);
    holes_.push_back(hole6);

    for (int i=0; i < holes_.length(); i++) {
        addItem(holes_[i]);
    }


    // Create & add the player
    player_ = new Player();
    player_->setPos(800 / 2 - 42, SCENE_HEIGHT / 2);
    addItem(player_);


    // Create & add Health
    health_ = player_->getHealth();
    addItem(health_);

    // Create & add Ammo
    ammo_ = new Ammo();
    ammo_->setPos(0, 40);
    addItem(ammo_);

    // Create & add the ground
//    ground = new Ground();
//    ground->setPos(200, SCENE_GROUND_HEIGHT - 66);
//    addItem(ground);

    // Create & add the monster
    monster_ = new Monster();
    monster_->setPos(2500, SCENE_GROUND_HEIGHT - monster_->boundingRect().height());
    addItem(monster_);

    //Create & add the goblins
    goblins_.push_back(new Goblin(1250, 282 - 45));
    goblins_.push_back(new Goblin(1600, 282 - 45));
    addItem(goblins_[0]);
    addItem(goblins_[1]);

    //Create & add 4  rect platforms
    rectplatforms_.push_back(new RectPlatform(110, SCENE_HEIGHT - 120, 20, 90));
    rectplatforms_.push_back(new RectPlatform(85, SCENE_HEIGHT - 120, 55, 25));

    rectplatforms_.push_back(new RectPlatform(790, 195, 114, 65));
    rectplatforms_.push_back(new RectPlatform(955, 236, 51, 38));

    rectplatforms_.push_back(new RectPlatform(1061, 282, 811, 90)); //1

    rectplatforms_.push_back(new RectPlatform(1992, 234, 51, 38)); //1
    rectplatforms_.push_back(new RectPlatform(2145, 189, 53, 38));
    rectplatforms_.push_back(new RectPlatform(2339, 368, 50, 45));



    addItem(rectplatforms_[0]);
    addItem(rectplatforms_[1]);
    addItem(rectplatforms_[2]);
    addItem(rectplatforms_[3]);

    addItem(rectplatforms_[4]);
    addItem(rectplatforms_[5]);
    addItem(rectplatforms_[6]);
    addItem(rectplatforms_[7]);

    // Create & add 4 Potions
    Potion * potion1 = new Potion();
    Potion * potion2 = new Potion();
    Potion * potion3 = new Potion();
    Potion * potion4 = new Potion();

    potion1->setPos(795, 164);
    potion2->setPos(850, 164);
    potion3->setPos(2440, 368 - 30);
    potion4->setPos(69, SCENE_GROUND_HEIGHT - 61);

    potions_.push_back(potion1);
    potions_.push_back(potion2);
    potions_.push_back(potion3);
    potions_.push_back(potion4);

    for (int i=0; i < potions_.length(); i++) {
        addItem(potions_[i]);
    }

    // Create & add 4 ammo Book
    Book * book1 = new Book();
    Book * book2 = new Book();
    Book * book3 = new Book();
    Book * book4 = new Book();
    Book * book5 = new Book();

    book1->setPos(820, 170);
    book2->setPos(880, 170);
    book3->setPos(20, SCENE_GROUND_HEIGHT - 25);
    book4->setPos(120, SCENE_HEIGHT - 180);
    book5->setPos(2480, 368 - 25);

    books_.push_back(book1);
    books_.push_back(book2);
    books_.push_back(book3);
    books_.push_back(book4);
    books_.push_back(book5);


    for (int i=0; i < books_.length(); i++) {
        addItem(books_[i]);
    }


}


QGraphicsItem *Scene::collidingPlatforms()
{

    QList<QGraphicsItem*> items =  player_->collidingItems();
    for (int i = 0; i< items.size(); i++){
        if ( typeid (*items[i]) == typeid (RectPlatform)){
            return items[i];
        }
    }
    return 0;
}

bool Scene::handleCollisionWithRectItems()
{

    QGraphicsItem * item = collidingPlatforms();

    if(item){

        player_->setTouchedPlatform(item);
        //to the right
        //only isleft
        if (!player_->getIs_Left() && player_->getState() >0){

            if(player_->x() >= item->boundingRect().toRect().x()){
                return false;}

            if (player_->isTouchingPlatform(item) && player_->isTouchingFeet(item) ){

                return false;
            }



        }
        //to the left
        else if (player_->getIs_Left() && player_->getState() <0 ){

            if(player_->x() <= item->boundingRect().toRect().x()){
                return false;
            }
            if (player_->isTouchingPlatform(item) && player_->isTouchingFeet(item) ){

                return false;
            }


        }
        return true;

    }

    player_->setTouchedPlatform(0);
    return false;
}


QGraphicsItem *Scene::collidingConsumable()
{

    QList<QGraphicsItem*> items =  player_->collidingItems();
    for (int i = 0; i< items.size(); i++){
        if (dynamic_cast<Consumable*>(items[i])){
            return items[i];
        }
    }
    return 0;
}

QGraphicsItem *Scene::checkIfTheFloorIsHole(){
    QList<QGraphicsItem*> items =  player_->collidingItems();
    for (int i = 0; i< items.size(); i++){
        if ( typeid (*items[i]) == typeid (Hole)){
            return items[i];

        }
    }
    return 0;
}

bool Scene::handleCollisionWithHole()
{

    QGraphicsItem * item = checkIfTheFloorIsHole();

    if(item){
        if((player_->x() - 13 > item->x()) && ((player_->x() +  31) < item->x()  + 130)){
            return true;
        }
    }
    return false;
}


bool Scene::checkCollisionConsumable(){
    QGraphicsItem * item = collidingConsumable();
    if(item) {
        if(typeid (*item) == typeid (Potion)) health_->increaseHealth(3);
        else if(typeid (*item) == typeid (Book)) ammo_->increaseAmmo(2);
        delete item;
        return true;
    }
    return false;
}


void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Add All
    painter->fillRect(
                QRectF(0, 0, width(), height()),
                *background_image_);
}






