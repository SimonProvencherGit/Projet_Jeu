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


void loadimages() { //Initialisation de toute les images.
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
    ListImages[21] = make_unique<QPixmap>();
    ListImages[21]->load("Textures\\Ennemis\\big_mama.png");
    ListImages[22] = make_unique<QPixmap>();
    ListImages[22]->load("Textures\\Ennemis\\big_mama-d.png");
    ListImages[23] = make_unique<QPixmap>();
    ListImages[23]->load("Textures\\Pup\\life.png");

    ListImages[24] = make_unique<QPixmap>();
    ListImages[24]->load("Textures\\Numbers\\0.png");
    ListImages[25] = make_unique<QPixmap>();
    ListImages[25]->load("Textures\\Numbers\\1.png");
    ListImages[26] = make_unique<QPixmap>();
    ListImages[26]->load("Textures\\Numbers\\2.png");
    ListImages[27] = make_unique<QPixmap>();
    ListImages[27]->load("Textures\\Numbers\\3.png");
    ListImages[28] = make_unique<QPixmap>();
    ListImages[28]->load("Textures\\Numbers\\4.png");
    ListImages[29] = make_unique<QPixmap>();
    ListImages[29]->load("Textures\\Numbers\\5.png");
    ListImages[30] = make_unique<QPixmap>();
    ListImages[30]->load("Textures\\Numbers\\6.png");
    ListImages[31] = make_unique<QPixmap>();
    ListImages[31]->load("Textures\\Numbers\\7.png");
    ListImages[32] = make_unique<QPixmap>();
    ListImages[32]->load("Textures\\Numbers\\8.png");
    ListImages[33] = make_unique<QPixmap>();
    ListImages[33]->load("Textures\\Numbers\\9.png");

	ListImages[34] = make_unique<QPixmap>();    
	ListImages[34]->load("Textures\\Ennemis\\orbiter.png");
	ListImages[35] = make_unique<QPixmap>();
	ListImages[35]->load("Textures\\Ennemis\\orbiter-d.png");
	ListImages[36] = make_unique<QPixmap>();
	ListImages[36]->load("Textures\\Pup\\addLife.png");
	ListImages[37] = make_unique<QPixmap>();
	ListImages[37]->load("Textures\\Pup\\addAmo.png");
    ListImages[38] = make_unique<QPixmap>();
    ListImages[38]->load("Textures\\Sprites\\barrel_roll.png");
    ListImages[39] = make_unique<QPixmap>();
    ListImages[39]->load("Textures\\Sprites\\barrel_roll-d.png");

    ListImages[40] = make_unique<QPixmap>();
    ListImages[40]->load("Textures\\bullets\\canon.png");
    ListImages[41] = make_unique<QPixmap>();
    ListImages[41]->load("Textures\\Ennemis\\sideBomber.png");
    ListImages[42] = make_unique<QPixmap>();
    ListImages[42]->load("Textures\\Ennemis\\sideBomber-d.png");
    ListImages[43] = make_unique<QPixmap>();
    ListImages[43]->load("Textures\\Sprites\\boss2.png");
    ListImages[44] = make_unique<QPixmap>();
    ListImages[44]->load("Textures\\Sprites\\boss2-d.png");
    ListImages[46] = make_unique<QPixmap>();
    ListImages[46]->load("Textures\\Ennemis\\boss3_main.png");
    ListImages[47] = make_unique<QPixmap>();
    ListImages[47]->load("Textures\\Ennemis\\boss3_main-d.png");
    ListImages[48] = make_unique<QPixmap>();
    ListImages[48]->load("Textures\\Ennemis\\boss3_side.png");
    ListImages[49] = make_unique<QPixmap>();
    ListImages[49]->load("Textures\\Ennemis\\boss3_side-d.png");
    ListImages[50] = make_unique<QPixmap>();
    ListImages[50]->load("Textures\\Ennemis\\exploder.png");
    ListImages[51] = make_unique<QPixmap>();
    ListImages[51]->load("Textures\\Ennemis\\exploder-d.png");
    ListImages[52] = make_unique<QPixmap>();
    ListImages[52]->load("Textures\\Sprites\\turret.png");
    ListImages[53] = make_unique<QPixmap>();
    ListImages[53]->load("Textures\\Sprites\\turret-d.png");
    ListImages[54] = make_unique<QPixmap>();
    ListImages[54]->load("Textures\\Ennemis\\exploder.png");
    ListImages[55] = make_unique<QPixmap>();
    ListImages[55]->load("Textures\\Ennemis\\exploder-d.png");
	ListImages[56] = make_unique<QPixmap>();
	ListImages[56]->load("Textures\\Ennemis\\tankR.png");
	ListImages[57] = make_unique<QPixmap>();
	ListImages[57]->load("Textures\\Ennemis\\tankR-d.png");

	ListImages[58] = make_unique<QPixmap>();
	ListImages[58]->load("Textures\\Numbers\\0-R.png");
	ListImages[59] = make_unique<QPixmap>();
	ListImages[59]->load("Textures\\Numbers\\1-R.png");
	ListImages[60] = make_unique<QPixmap>();
	ListImages[60]->load("Textures\\Numbers\\2-R.png");
	ListImages[61] = make_unique<QPixmap>();
	ListImages[61]->load("Textures\\Numbers\\3-R.png");
	ListImages[62] = make_unique<QPixmap>();
	ListImages[62]->load("Textures\\Numbers\\4-R.png");
	ListImages[63] = make_unique<QPixmap>();
	ListImages[63]->load("Textures\\Numbers\\5-R.png");
	ListImages[64] = make_unique<QPixmap>();
	ListImages[64]->load("Textures\\Numbers\\6-R.png");
	ListImages[65] = make_unique<QPixmap>();
	ListImages[65]->load("Textures\\Numbers\\7-R.png");
	ListImages[66] = make_unique<QPixmap>();
	ListImages[66]->load("Textures\\Numbers\\8-R.png");
	ListImages[67] = make_unique<QPixmap>();
	ListImages[67]->load("Textures\\Numbers\\9-R.png");
	ListImages[68] = make_unique<QPixmap>();
	ListImages[68]->load("Textures\\Numbers\\x.png");

	ListImages[69] = make_unique<QPixmap>();
	ListImages[69]->load("Textures\\Sprites\\barrel_roll2.png");
	ListImages[70] = make_unique<QPixmap>();
	ListImages[70]->load("Textures\\Sprites\\barrel_roll2-d.png");


	

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
            jeux->executionJeu(1); // Call executionJeu if the object exists
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
    QOpenGLWidget* glWidget = new QOpenGLWidget();// fait que le jeux est une application opengl
    view->setViewport(glWidget);// set le view pour opengl

    // Ajouter du antialiasing et Smoothing des pixels.
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    view->fitInView(GameScene->sceneRect(), Qt::KeepAspectRatio);
    view->showFullScreen();
    view->fitInView(GameScene->sceneRect(), Qt::KeepAspectRatio);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() { firststart(); });
    timer.start(16); // 60 FPS (16 ms per frame)

    //Augmenter Framerate
    QTimer frametimer;
    QObject::connect(&frametimer, &QTimer::timeout, [&]() { updateframes(); });
    frametimer.start(10);

    return app.exec();
}

