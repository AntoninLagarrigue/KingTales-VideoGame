#include <QApplication>
#include <QMediaPlayer>
#include <QIcon>
#include <QSplashScreen>
#include "Game.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);



    //Add an icon
    app.setWindowIcon(QIcon(":/sprites/icon.png"));


//    //Add Splash Screen
//    QSplashScreen *splash = new QSplashScreen;
//    splash->setPixmap(QPixmap(":/sprites/screen.jpg"));
//    splash->show();

//    // Play background music
//    QMediaPlayer background_music;
//    background_music.setMedia(QUrl(":/sounds/bgMusic.ogg"));
//    background_music.play();

    // Create Game
    Game game;

    game.setWindowTitle("The Elder Scrolls VI (non)");
    game.show();
    game.start();

//    QTimer::singleShot(400,splash,SLOT(close()));
//    QTimer::singleShot(400,&game,SLOT(show()));

    return app.exec();
}
