#include <iostream>
#include "Interface.h"
#include "Menu.h"
#include "globalobjects.h"



//Variables globales pour le main
int frameCount = 0;
bool isSquareVisible = true;
bool fullscreen = false;

bool first = true;
extern std::unique_ptr<Interface> jeux = nullptr;

void loadimages(){ //Initalisation de toute les images.
    ListImages[0] = make_unique<QPixmap>();
    ListImages[0]->load("Textures\\Ennemis\\BasicEnnemi.png");
    ListImages[1] = make_unique<QPixmap>();
    ListImages[1]->load("Textures\\Ennemis\\BasicEnnemi-d.png");
    ListImages[2] = make_unique<QPixmap>();
    ListImages[2]->load("Textures\\Ennemis\\artilleur.png");
    ListImages[3] = make_unique<QPixmap>();
    ListImages[3]->load("Textures\\Ennemis\\artilleur-d.png");
    ListImages[4] = make_unique<QPixmap>();
    ListImages[4]->load("Textures\\Ennemis\\divebomber.png");
    ListImages[5] = make_unique<QPixmap>();
    ListImages[5]->load("Textures\\Ennemis\\divebomber-d.png");
    ListImages[6] = make_unique<QPixmap>();
    ListImages[6]->load("Textures\\bullets\\basicbullet.png");
    ListImages[7] = make_unique<QPixmap>();
    ListImages[7]->load("Textures\\Ennemis\\BasicEnnemi-d.png");
    ListImages[8] = make_unique<QPixmap>();
    ListImages[8]->load("Textures\\Ennemis\\BasicEnnemi-d.png");


}

void firststart() {
    if (first) {
        loadimages();
        first = false; // Set first to false after the first run
        jeux = std::make_unique<Interface>();// Create an instance of a concrete implementation
        //loadimages();
    }
    else {
        if (jeux) {
            jeux->executionJeu(0); // Call executionJeu if the object exists
        }
    }
}
 

int main(int argc, char* argv[]) {
    //QPixmap ListImage[50];
    loadsettings();
    QApplication app(argc, argv);

    GameScene = new QGraphicsScene();
    GameScene->setSceneRect(0, 0, 1920, 1080); // Set the scene dimensions

    view = new QGraphicsView(GameScene);
    //view->setRenderHint(QPainter::Antialiasing); // Enable smooth rendering
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setContentsMargins(0, 0, 0, 0);
    // Remove the border and background
    view->setFrameStyle(QFrame::NoFrame); // Removes the frame (border)
    view->setBackgroundBrush(Qt::NoBrush); // Removes the background color

    view->fitInView(GameScene->sceneRect(), Qt::KeepAspectRatio);
    view->showFullScreen(); // Show in full-screen mode

    // Call fitInView again after switching to full screen
    view->fitInView(GameScene->sceneRect(), Qt::KeepAspectRatio);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() { firststart(); });
    timer.start(16); // ~60 FPS (16 ms per frame)

    return app.exec();
}

