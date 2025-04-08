#include <iostream>
#include "Interface.h"
#include "Menu.h"
#include "globalobjects.h"
#include <QOpenGLwidget>


//Variables globales pour le main
int frameCount = 0;
bool isSquareVisible = true;
bool fullscreen = false;




void updateframes()
{
    GameScene->update();
}
;
int main(int argc, char* argv[]) {

    //QPixmap ListImage[50];
    loadsettings();
    music.playMusic("MainMenu.wav", 65548, 63989);
    QApplication app(argc, argv);


    GameScene = new QGraphicsScene();
    GameScene->setSceneRect(0, 0, 1920, 1080);

    GererMenu* menu = new GererMenu();


    view = new QGraphicsView(GameScene);
    view->setScene(menu);
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

    //QTimer timer;
    //QObject::connect(&timer, &QTimer::timeout, [&]() { firststart(); });
    //timer.start(16); // 60 FPS (16 ms per frame)

    //Augmenter Framerate

    return app.exec();
}

