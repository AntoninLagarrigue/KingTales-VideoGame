#include "Game.h"
#include "FireBall.h"

Game::Game(QWidget *parent) : QGraphicsView(parent)
{

    // Window config
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setSceneRect(QRectF(0,0, WINDOW_WIDTH, WINDOW_HEIGHT));
    //setInteractive(false);
    playAgainButton_ = new Button(QString("Play again"));
    connect(playAgainButton_,SIGNAL(clicked()),this,SLOT(restartGame()));
    playAgainButton_->setPos(285,180);

}
void Game::start(){

    on_a_platform_ = false;
    isMovable = true;
    // Create  & set the scene to the view

    scene_ = new Scene(this);
    setScene(scene_);
    setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    playAgainButton_->setPos(285,180);
    // playAgainButton_->setPos(285,180);

    // left right movement timer
    move_timer_.setTimerType(Qt::PreciseTimer);
    move_timer_.setInterval(25);
    connect(&move_timer_, SIGNAL(timeout()), this, SLOT(move()));

    // Health timer
    health_timer.setTimerType(Qt::PreciseTimer);
    health_timer.setInterval(5);
    connect(&health_timer,SIGNAL(timeout()),this,SLOT(isGameOver()));
    health_timer.start();

    // gravity timer
    gravity_timer_.setTimerType(Qt::PreciseTimer);
    gravity_timer_.setInterval(20);
    connect(&gravity_timer_, SIGNAL(timeout()), this, SLOT(gravity()));
    gravity_timer_.start();

    // Create jump animation
    jumpAnimation_ = new QPropertyAnimation(this);
    jumpAnimation_->setTargetObject(this);
    jumpAnimation_->setPropertyName("jumpCoeff");
    jumpAnimation_->setStartValue(0);
    jumpAnimation_->setKeyValueAt(0.5, 1);
    jumpAnimation_->setEndValue(0);
    jumpAnimation_->setDuration(800);
    jumpAnimation_->setEasingCurve(QEasingCurve::OutInQuad);
    connect(this, SIGNAL(jumpCoeffChanged(qreal)), this, SLOT(jump()));

    this->setEnabled(true);
}
Game::~Game(){}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(!isMovable) return;
    if (event->isAutoRepeat()){
        return;}

    switch (event->key()) {
    case Qt::Key_Left:
        if(scene_ == NULL) return;
        scene_->getPlayer()->setState(-1);
        scene_->getPlayer()->setIs_Left(true);
        if (scene_->getPlayer()->getState() == 0){
            move_timer_.stop();
        }
        else if (!move_timer_.isActive()){
            move_timer_.start();

        }

        break;
    case Qt::Key_Right:
        if(scene_ == NULL) return;
        scene_->getPlayer()->setState(1);
        scene_->getPlayer()->setIs_Left(false);
        if (scene_->getPlayer()->getState() == 0){
            move_timer_.stop();
        }
        else if (!move_timer_.isActive()){
            move_timer_.start();

        }

        break;
    case Qt::Key_Space:

        // If the player already is jumping
        if(gravity_timer_.isActive()) return;
        if (jumpAnimation_->state() == QAbstractAnimation::Stopped){
            jumpAnimation_->start();}

        break;
    case Qt::Key_V:
        if(scene_->getAmmo()->getAmmoNb() > 0) {
            scene_->addItem(scene_->getPlayer()->throwFireball());
            scene_->getAmmo()->decreaseAmmo(1);
        }
        break;

    }
}


void Game::keyReleaseEvent(QKeyEvent *event)
{
    if(!isMovable) return;
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_Left:

        scene_->getPlayer()->setState(1);
        scene_->getPlayer()->setIs_Left(true);
        if (scene_->getPlayer()->getState() == 0){
            move_timer_.stop();
        }
        else if (!move_timer_.isActive()){
            move_timer_.start();

        }

        break;
    case Qt::Key_Right:

        scene_->getPlayer()->setState(-1);
        scene_->getPlayer()->setIs_Left(false);
        if (scene_->getPlayer()->getState() == 0){
            move_timer_.stop();
        }
        else if (!move_timer_.isActive()){
            move_timer_.start();

        }
        break;

    }
}

void Game::handleEvents(){}

void Game::gameOver()
{
    displayGameOver();
}

void Game::displayGameOver()
{
    isMovable = false;
    this->setEnabled(false);
    for (size_t i = 0, n = scene_->items().size(); i < n; i++){
        scene_->items()[i]->setEnabled(false);
    }
    scene_->items().clear();
    scene_->blockSignals(true);
    scene_->clear();
    scene_->blockSignals(false);
    drawPanel(0,0,SCENE_WIDTH,768,Qt::black,0.85);

 //  drawPanel(256,80,256,256,Qt::red,0.5);
    this->jumpAnimation_->stop();
    this->gravity_timer_.stop();
    this->move_timer_.stop();
    this->health_timer.stop();
    disconnect(&move_timer_, SIGNAL(timeout()), 0, 0);
    disconnect(&gravity_timer_, SIGNAL(timeout()), 0, 0);
    disconnect(&health_timer, SIGNAL(timeout()), 0, 0);
    disconnect(this, SIGNAL(jumpCoeffChanged(qreal)), 0, 0);

    this->setEnabled(true);

    scene_->addItem(playAgainButton_);

}
void Game::restartGame(){
    qDebug() << "Start" << endl;
    start();
}
void Game::gravity()
{
    checkIfMonster();
    // The players falls
    scene_->getPlayer()->setPos(scene_->getPlayer()->x(),scene_->getPlayer()->y() + 10);

    // If the player is touching something while falling
    if(handleCollisionWhileFalling()){
        gravity_timer_.stop();
        on_a_platform_ = true;

    }
    // when the player is arriving beneath the ground
    else if(scene_->getPlayer()->y() + scene_->getPlayer()->boundingRect().height() >= SCENE_GROUND_HEIGHT && !scene_->handleCollisionWithHole()){
        scene_->getPlayer()->setPos(scene_->getPlayer()->x(), SCENE_GROUND_HEIGHT - scene_->getPlayer()->boundingRect().height());
        gravity_timer_.stop();
        scene_->getPlayer()->setTouchedPlatform(0);
        new_ground = 0;
        on_a_platform_ = false;
    }
    if(scene_->getPlayer()->y() >= SCENE_HEIGHT) {
        scene_->getHealth()->setHealthNb(0);
    }

}
void Game::isGameOver(){
    if(scene_->getHealth()->getHealthNb() <= 0) {
        gameOver();
    }
}
void Game::jump()
{

    scene_->checkCollisionConsumable();
    checkIfMonster();

    if(jumpAnimation_->state() == QAbstractAnimation::Stopped){
        return;
    }

    QGraphicsItem* item = scene_->collidingPlatforms();
    if(item){
        // if the head is touching the platform
        if(scene_->getPlayer()->isTouchingHead(item)){
            jumpAnimation_->stop();

            // if not touching the player goes back to the ground
            if(!scene_->getPlayer()->isTouchingPlatform(item)){
                scene_->getPlayer()->setPos(scene_->getPlayer()->x(), GROUND_HEIGHT - scene_->getPlayer()->boundingRect().height());
                on_a_platform_ = false;
                return;
            }
        }
        // if not we handle the collision while falling
        else{
            if(handleCollisionWhileJumpingDown()){
                return;
            }
        }
    }
    //Cannot jump while falling
    if(gravity_timer_.isActive()){
        return;
    }

    qreal y = (GROUND_HEIGHT  - scene_->getPlayer()->boundingRect().height()) - jumpAnimation_->currentValue().toReal() * JUMP_HEIGHT;

    //&& scene_->getPlayer()->y() + scene_->getPlayer()->boundingRect().height() < scene_->getPlayer()->getTouchedPlatform()->boundingRect().toRect().y()
    if(on_a_platform_==true){
        y = (new_ground->boundingRect().toRect().y() - scene_->getPlayer()->boundingRect().height()) - jumpAnimation_->currentValue().toReal() * JUMP_HEIGHT;
        if(!scene_->getPlayer()->isTouchingPlatform(new_ground) &&  jumpCoeff_ < 0.4 ) {
            if( scene_->getPlayer()->x() + scene_->getPlayer()->boundingRect().width() +10 < new_ground->boundingRect().toRect().x() || scene_->getPlayer()->x() - 10> new_ground->boundingRect().toRect().x() + new_ground->boundingRect().width()){
                if(scene_->getPlayer()->y() < GROUND_HEIGHT){
                    gravity_timer_.start();
                    jumpAnimation_->stop();
                    return;
                }
            }
            else {
                scene_->getPlayer()->setTouchedPlatform(new_ground);
            }
        }
    }

    if(scene_->handleCollisionWithHole()){     
        if(jumpCoeff_ < 0.4 ) {         
            gravity_timer_.start();
            jumpAnimation_->stop();
            return;
        }
    }

scene_->getPlayer()->setPos(scene_->getPlayer()->x(), y);


}

void Game::move()
{
    checkIfMonster();
    checkIfTheFloorIsLava();
    scene_->checkCollisionConsumable();
    if(scene_->handleCollisionWithHole()) {
        gravity_timer_.start();
        gravity();
    }

    // If falling then no moving
    if(gravity_timer_.isActive()){
        return;
    }

    //If advance in emptiness
    if(scene_->getPlayer()->getTouchedPlatform() == 0  && scene_->getPlayer()->y() < GROUND_HEIGHT - scene_->getPlayer()->boundingRect().height()  &&jumpAnimation_->state() == QAbstractAnimation::Stopped){
        gravity_timer_.start();
    }

    if (scene_->handleCollisionWithRectItems()) return;

    // Left
    if (scene_->getPlayer()->getState() < 0)
    {

        if (scene_->getPlayer()->pos().x() - 32 > 0) scene_->getPlayer()->moveBy(- 5, 0);
    }
    // Right
    else if (scene_->getPlayer()->getState() > 0)
    {

        if (scene_->getPlayer()->pos().x() + 32 < SCENE_WIDTH) scene_->getPlayer()->moveBy(5, 0);
    }

    scene_->getPlayer()->nextFrame();
    moveView();

}

void Game::moveView(){
    if(scene_->getPlayer()->x() > SCENE_WIDTH - WINDOW_WIDTH/2 - 42 || scene_->getPlayer()->x() <  WINDOW_WIDTH/2 - 42  )
        return;
    scene_->getHealth()->setPos(scene_->getPlayer()->x() - WINDOW_WIDTH/2 + 42, 0);
    scene_->getAmmo()->setPos(scene_->getPlayer()->x() - WINDOW_WIDTH/2 + 42, 40);
    playAgainButton_->setPos(scene_->getPlayer()->x() - 90,180);
    setSceneRect((scene_->getPlayer()->x() - WINDOW_WIDTH/2 + 42),0, WINDOW_WIDTH, WINDOW_HEIGHT);

}


bool Game::handleCollisionWhileFalling()
{

    QGraphicsItem* platform =  scene_->collidingPlatforms();
    // Si on touche une plateforme
    if(platform) {
        if(scene_->getPlayer()->isTouchingFeet(platform) && scene_->getPlayer()->isTouchingPlatform(platform) ){
            scene_->getPlayer()->setPos(scene_->getPlayer()->x(), platform->boundingRect().toRect().y() - scene_->getPlayer()->boundingRect().height());
            scene_->getPlayer()->setTouchedPlatform(platform);
            new_ground = platform;
            jumpAnimation_->stop();
            on_a_platform_ = true;
            return true;
        }

    }
    // Sinon rien
    else {
        scene_->getPlayer()->setTouchedPlatform(0);
        new_ground = 0;
        on_a_platform_ = false;
    }
    return false;
}

bool Game::handleCollisionWhileJumpingDown()
{

    QGraphicsItem* platform =  scene_->collidingPlatforms();

    // Si on touche une plateforme alors qu'on était pas sur une plateforme
    if(platform && !on_a_platform_) {
        if(scene_->getPlayer()->isTouchingFeet(platform) && scene_->getPlayer()->isTouchingPlatform(platform)  ){
            scene_->getPlayer()->setTouchedPlatform(platform);
            new_ground = platform;
            jumpAnimation_->stop();
            on_a_platform_ = true;
            return true;
        }

    }
    // Si on touche une plateforme et qu'on était sur une plateforme
    else if (platform && on_a_platform_){

        return false;
    }

    // Si on touche pas
    else if (!platform){
        scene_->getPlayer()->setTouchedPlatform(0);
        new_ground = 0;
        on_a_platform_ = false;
    }
    return false;
}


qreal Game::jumpCoeff() const
{
    return jumpCoeff_;
}

void Game::setJumpCoeff(const qreal &jumpCoeff)
{
    if (jumpCoeff_ == jumpCoeff)
        return;

    jumpCoeff_ = jumpCoeff;
    emit jumpCoeffChanged(jumpCoeff_);
}
void Game::checkIfTheFloorIsLava(){
    QList<QGraphicsItem*> items =  scene_->getPlayer()->collidingItems();
    for (int i = 0; i< items.size(); i++){
        if ( typeid (*items[i]) == typeid (Ground)) {
            scene_->getHealth()->setHealthNb(scene_->getHealth()->getHealthNb() - 1);
        }


    }
}

void Game::checkIfMonster(){
    QList<QGraphicsItem *> items = scene_->getPlayer()->collidingItems();

           for (int i = 0, n = items.size(); i < n; ++i){
               if (typeid(*(items[i])) == typeid(Monster)){
                   scene_->getHealth()->setHealthNb(scene_->getHealth()->getHealthNb() - 4);
               }
               if (typeid(*(items[i])) == typeid(Goblin)){
                   scene_->getHealth()->setHealthNb(scene_->getHealth()->getHealthNb() - 1);
               }
           }
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene_->addItem(panel);
}


