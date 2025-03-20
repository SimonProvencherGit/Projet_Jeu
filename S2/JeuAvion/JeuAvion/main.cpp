#include <iostream>
#include "Interface.h"
#include "Menu.h"
#include "globalobjects.h"
#include <QOpenGLwidget>


//Variables globales pour le main
int frameCount = 0;
bool isSquareVisible = true;
bool fullscreen = false;

bool first = true;
extern std::unique_ptr<Interface> jeux = nullptr;

void updateframes()
{
    GameScene->update();
}


void loadimages(){ //Initialisation de toute les images.
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
    ListImages[7]->load("Textures\\Ennemis\\aimbot.png");
    ListImages[8] = make_unique<QPixmap>();
    ListImages[8]->load("Textures\\Ennemis\\aimbot-d.png");
    ListImages[9] = make_unique<QPixmap>();
    ListImages[9]->load("Textures\\Ennemis\\big_mama.png");
    ListImages[10] = make_unique<QPixmap>();
    ListImages[10]->load("Textures\\Ennemis\\big_mama-d.png");
    ListImages[11] = make_unique<QPixmap>();
    ListImages[11]->load("Textures\\Ennemis\\boss1_main.png");
    ListImages[12] = make_unique<QPixmap>();
    ListImages[12]->load("Textures\\Ennemis\\boss1_main-d.png");
    ListImages[13] = make_unique<QPixmap>();
    ListImages[13]->load("Textures\\Ennemis\\boss1_side.png");
    ListImages[14] = make_unique<QPixmap>();
    ListImages[14]->load("Textures\\Ennemis\\boss1_side-d.png");
    ListImages[15] = make_unique<QPixmap>();
    ListImages[15]->load("Textures\\Ennemis\\tank.png");
    ListImages[16] = make_unique<QPixmap>();
    ListImages[16]->load("Textures\\Ennemis\\tank-d.png");
    ListImages[17] = make_unique<QPixmap>();
    ListImages[17]->load("Textures\\bullets\\homing.png");
    ListImages[18] = make_unique<QPixmap>();
    ListImages[18]->load("Textures\\bullets\\homing-d.png");
    ListImages[19] = make_unique<QPixmap>();
    ListImages[19]->load("Textures\\bullets\\laser.png");
    ListImages[20] = make_unique<QPixmap>();
    ListImages[20]->load("Textures\\bullets\\laser2.png");


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
;

int main(int argc, char* argv[]) {
    //QPixmap ListImage[50];
    loadsettings();
    QApplication app(argc, argv);

    GameScene = new QGraphicsScene();
    GameScene->setSceneRect(0, 0, 1920, 1080);

    view = new QGraphicsView(GameScene);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setContentsMargins(0, 0, 0, 0);
    // Remove the border and background
    view->setFrameStyle(QFrame::NoFrame); 
    view->setBackgroundBrush(Qt::NoBrush); 
    //QOpenGLWidget* glWidget = new QOpenGLWidget();// fait que le jeux est une application opengl
   // view->setViewport(glWidget);// set le view pour opengl

    // Ajouter du antialiasing et Smoothing des pixels.
    //view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    view->fitInView(GameScene->sceneRect(), Qt::KeepAspectRatio);
    view->showFullScreen(); 
    view->fitInView(GameScene->sceneRect(), Qt::KeepAspectRatio);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() { firststart(); });
    timer.start(16); // 60 FPS (16 ms per frame)

    //Augmenter Framerate
    //QTimer frametimer;
   // QObject::connect(&frametimer, &QTimer::timeout, [&]() { updateframes(); });
    //frametimer.start(30);

    return app.exec();
}

