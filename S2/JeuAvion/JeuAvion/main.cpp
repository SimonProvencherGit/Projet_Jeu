#include <iostream>
#include "Interface.h"
#include "Menu.h"
#include "globalobjects.h"

Interface jeux;

   // Global variables for the scene and shapes
//

QGraphicsEllipseItem* circle;
int frameCount = 0;
bool isSquareVisible = true;
bool fullscreen = false;

/*int main(int argc, char* argv[]) {
    loadsettings();
    QApplication app(argc, argv);
    
    GameScene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(GameScene);

    
    
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() { jeux.executionJeu(1); });
    timer.start(16); // ~60 FPS (16 ms per frame)
 
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    view->show();
    view->showFullScreen();
    return app.exec();
}*/
 

int main(int argc, char* argv[]) {
    loadsettings();
    QApplication app(argc, argv);

    GameScene = new QGraphicsScene();
    GameScene->setSceneRect(0, 0, 1920, 1080); // Set the scene dimensions

    QGraphicsView* view = new QGraphicsView(GameScene);
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
    QObject::connect(&timer, &QTimer::timeout, [&]() { jeux.executionJeu(0); });
    timer.start(16); // ~60 FPS (16 ms per frame)

    return app.exec();
}

