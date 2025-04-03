#include "JeuBackground.h"
#include "globalobjects.h"

backgroundmanager::backgroundmanager()
{
	//En creation default au background ocean
	Background1 = new Sprite("spritesheet.png", "spritesheet.json");
	Background2 = new Sprite("spritesheet.png", "spritesheet.json");
	Background1->setpos(-175, 0);
	Background1->pixmapItem->setScale(0.75);
	Background1->pixmapItem->show();
	GameScene->addItem(Background1->pixmapItem);
	Background2->setpos(-175, -1284);
	Background2->pixmapItem->setScale(0.75);
	Background2->pixmapItem->show();
	GameScene->addItem(Background2->pixmapItem);
	Background2->setframe(0);


	timerBack1 = new QTimer();
	timerBack2 = new QTimer();
	QObject::connect(timerBack1, &QTimer::timeout, [=]() {
		if (currentback1y >= 1284) {
			currentback1y = 0;
			Background1->pixmapItem->setPos(-175, currentback1y);
			GameScene->update();
		}

		Background1->pixmapItem->setPos(-175, currentback1y + 1);
		currentback1y = currentback1y + 3;
		GameScene->update();
		});


	QObject::connect(timerBack2, &QTimer::timeout, [=]() {
		if (currentback2y >= 0) {
			currentback2y = -1284;
			Background2->pixmapItem->setPos(-175, currentback2y);
			GameScene->update();
		}

		Background2->pixmapItem->setPos(-175, currentback2y + 1);
		currentback2y = currentback2y + 3;
		GameScene->update();
		});
	
}
void backgroundmanager::setocean()
{
	if (Background1 == nullptr && Background2 == nullptr) 
	{
		Background1 = new Sprite("ocean.png", "ocean.json");
		Background2 = new Sprite("ocean.png", "ocean.json");
		mapframetimer = 200;
		return;
	}
	else
	{
		delete Background1;
		delete Background2;
		Background1 = new Sprite("ocean.png", "ocean.json");
		Background2 = new Sprite("ocean.png", "ocean.json");
		mapframetimer = 200;
	}
	

}
void backgroundmanager::setforest()
{
	if (Background1 == nullptr && Background2 == nullptr)
	{
		Background1 = new Sprite("forest.png", "forest.json");
		Background2 = new Sprite("forest.png", "forest.json");
		Background1->setpos(-175, 0);
		Background1->pixmapItem->setScale(0.75);
		Background1->pixmapItem->show();
		Background1->setframe(0);
		GameScene->addItem(Background1->pixmapItem);
		Background2->setpos(-175, -1284);
		Background2->pixmapItem->setScale(0.75);
		Background2->pixmapItem->show();
		GameScene->addItem(Background2->pixmapItem);
		Background2->setframe(0);
		GameScene->update();
		mapframetimer = 500;
		return;
	}
	else
	{
		delete Background1;
		delete Background2;
		Background1 = new Sprite("forest.png", "forest.json");
		Background2 = new Sprite("forest.png", "forest.json");
		Background1->setpos(-175, 0);
		Background1->pixmapItem->setScale(0.75);
		Background1->pixmapItem->show();
		GameScene->addItem(Background1->pixmapItem);
		Background2->setpos(-175, -1284);
		Background2->pixmapItem->setScale(0.75);
		Background2->pixmapItem->show();
		GameScene->addItem(Background2->pixmapItem);
		Background2->setframe(0);
		GameScene->update();
		mapframetimer = 500;
	}
}
void backgroundmanager::setdesert()
{
	if (Background1 == nullptr && Background2 == nullptr)
	{
		Background1 = new Sprite("ocean.png", "ocean.json");
		Background2 = new Sprite("ocean.png", "ocean.json");
		mapframetimer = 10;
		return;
	}
	else
	{
		delete Background1;
		delete Background2;
		Background1 = new Sprite("ocean.png", "ocean.json");
		Background2 = new Sprite("ocean.png", "ocean.json");
		mapframetimer = 10;
	}
}
void backgroundmanager::setspace()
{
	if (Background1 == nullptr && Background2 == nullptr)
	{
		Background1 = new Sprite("space.png", "space.json");
		Background2 = new Sprite("space.png", "space.json");
		Background1->setpos(-175, 0);
		Background1->pixmapItem->setScale(0.75);
		Background1->pixmapItem->show();
		Background1->setframe(0);
		GameScene->addItem(Background1->pixmapItem);
		Background2->setpos(-175, -1284);
		Background2->pixmapItem->setScale(0.75);
		Background2->pixmapItem->show();
		GameScene->addItem(Background2->pixmapItem);
		Background2->setframe(0);
		GameScene->update();
		mapframetimer = 500;
		return;
	}
	else
	{
		delete Background1;
		delete Background2;
		Background1 = new Sprite("space.png", "space.json");
		Background2 = new Sprite("space.png", "space.json");
		Background1->setpos(-175, 0);
		Background1->pixmapItem->setScale(0.75);
		Background1->pixmapItem->show();
		GameScene->addItem(Background1->pixmapItem);
		Background2->setpos(-175, -1284);
		Background2->pixmapItem->setScale(0.75);
		Background2->pixmapItem->show();
		GameScene->addItem(Background2->pixmapItem);
		Background2->setframe(0);
		GameScene->update();
		mapframetimer = 500;
	}

}
void backgroundmanager::bougebackground() 
{
	if (Background1 == nullptr)
	{
		qDebug("Erreur t'est background sont null");
		return;
	}
	Background1->start(mapframetimer);
	Background2->start(mapframetimer);
	timerBack1->start(30);
	timerBack2->start(30);


}

void backgroundmanager::stopbackground()
{
	Background1->stop();
	Background2->stop();
	timerBack1->stop();
	timerBack2->stop();
}
//////////////////////////////////// EXPLOSIONS ////////////////////////////////

void explosionmanager::enemydeathexplosion(int posx, int posy)
{
	Sprite* spriteexplosion = new Sprite("explosion.png", "explosion.json");
	spriteexplosion->setpos(posx, posy);
	spriteexplosion->pixmapItem->setZValue(100);
	spriteexplosion->pixmapItem->setScale(1);
	spriteexplosion->pixmapItem->show();
	GameScene->addItem(spriteexplosion->pixmapItem);
	spriteexplosion->start(20);
	enemyexplosion.playSFX("explosion.wav");

	QTimer::singleShot(300, [=]() {
		delete spriteexplosion;
		});
}


void shakeScene(QGraphicsScene* scene, QGraphicsView* view, int duration, int magnitude) {
	
	QRectF originalScene = scene->sceneRect();
	originalScene.setX(0);
	originalScene.setY(0);
	GameScene->setSceneRect(originalScene);
	QTimer* timer = new QTimer(view);
	int elapsed = 0;

	QObject::connect(timer, &QTimer::timeout, [view, duration, magnitude, elapsed, originalScene, scene, timer]() mutable {
		if (elapsed < duration) {
			int offset = (rand() % (-magnitude)) + (magnitude);
			scene->setSceneRect(originalScene.translated(offset, 0)); // Shift the scene left and right
			elapsed += 20;
		}
		else {
			scene->setSceneRect(originalScene); //Remetre le Scene a l'orginal
			timer->stop();
			timer->deleteLater();
		}
		});

	timer->start(20);
}








//Ce code est horrible (I am lazy)
void explosionmanager::chainexplosion(int playerposy)
{
	int currentexplosionpos  = playerposy - 150;
	Sprite* expo1 = new Sprite("explosion.png", "explosion.json");
	Sprite* expo2 = new Sprite("explosion.png", "explosion.json");
	Sprite* expo3 = new Sprite("explosion.png", "explosion.json");
	Sprite* expo4 = new Sprite("explosion.png", "explosion.json");
	Sprite* expo5 = new Sprite("explosion.png", "explosion.json");
	Sprite* expo6 = new Sprite("explosion.png", "explosion.json");
	Sprite* expo7 = new Sprite("explosion.png", "explosion.json");
	Sprite* expo8 = new Sprite("explosion.png", "explosion.json");
	Sprite* expo9 = new Sprite("explosion.png", "explosion.json");
	Sprite* expo10 = new Sprite("explosion.png", "explosion.json");


	////////////////////////////
	expo1->setpos(0, 0);
	expo1->pixmapItem->setScale(2);
	expo1->pixmapItem->show();
	GameScene->addItem(expo1->pixmapItem);

	expo2->setpos(200, 0);
	expo2->pixmapItem->setScale(2);
	expo2->pixmapItem->show();
	GameScene->addItem(expo2->pixmapItem);

	expo3->setpos(400, 0);
	expo3->pixmapItem->setScale(2);
	expo3->pixmapItem->show();
	GameScene->addItem(expo3->pixmapItem);

	expo4->setpos(600, 0);
	expo4->pixmapItem->setScale(2);
	expo4->pixmapItem->show();
	GameScene->addItem(expo4->pixmapItem);

	expo5->setpos(800, 0);
	expo5->pixmapItem->setScale(2);
	expo5->pixmapItem->show();
	GameScene->addItem(expo5->pixmapItem);

	expo6->setpos(1000, 0);
	expo6->pixmapItem->setScale(2);
	expo6->pixmapItem->show();
	GameScene->addItem(expo6->pixmapItem);

	expo7->setpos(1200, 0);
	expo7->pixmapItem->setScale(2);
	expo7->pixmapItem->show();
	GameScene->addItem(expo7->pixmapItem);

	expo8->setpos(1400, 0);
	expo8->pixmapItem->setScale(2);
	expo8->pixmapItem->show();
	GameScene->addItem(expo8->pixmapItem);

	expo9->setpos(1600, 0);
	expo9->pixmapItem->setScale(2);
	expo9->pixmapItem->show();
	GameScene->addItem(expo9->pixmapItem);

	expo10->setpos(1800, 0);
	expo10->pixmapItem->setScale(2);
	expo10->pixmapItem->show();
	GameScene->addItem(expo10->pixmapItem);



	/////////////////////////
	expo1->pixmapItem->show();
	expo2->pixmapItem->show();
	expo3->pixmapItem->show();
	expo4->pixmapItem->show();
	expo5->pixmapItem->show();
	expo6->pixmapItem->show();
	expo7->pixmapItem->show();
	expo8->pixmapItem->show();
	expo9->pixmapItem->show();
	expo10->pixmapItem->show();
	////

	expo1->pixmapItem->setZValue(100);
	expo2->pixmapItem->setZValue(100);
	expo3->pixmapItem->setZValue(100);
	expo4->pixmapItem->setZValue(100);
	expo5->pixmapItem->setZValue(100);
	expo6->pixmapItem->setZValue(100);
	expo7->pixmapItem->setZValue(100);
	expo8->pixmapItem->setZValue(100);
	expo9->pixmapItem->setZValue(100);
	expo10->pixmapItem->setZValue(100);
	////


	QTimer* chainetimer = new QTimer;
	QObject::connect(chainetimer, &QTimer::timeout, [=]() mutable { //https://doc.qt.io/qt-6/qtimer.html
		if (currentexplosionpos > -200)
		{
			expo1->stop();
			expo2->stop();
			expo3->stop();
			expo4->stop();
			expo5->stop();
			expo6->stop();
			expo7->stop();
			expo8->stop();
			expo9->stop();
			expo10->stop();
			expo1->start(10);
			expo2->start(10);
			expo3->start(10);
			expo4->start(10);
			expo5->start(10);
			expo6->start(10);
			expo7->start(10);
			expo8->start(10);
			expo9->start(10);
			expo10->start(10);
			enemyexplosion.playSFX("explosion.wav");
			currentexplosionpos = currentexplosionpos - 50;
			expo1->setpos(0, currentexplosionpos);
			expo2->setpos(200, currentexplosionpos);
			expo3->setpos(400, currentexplosionpos);
			expo4->setpos(600, currentexplosionpos);
			expo5->setpos(800, currentexplosionpos);
			expo6->setpos(1000, currentexplosionpos);
			expo7->setpos(1200, currentexplosionpos);
			expo8->setpos(1400, currentexplosionpos);
			expo9->setpos(1600, currentexplosionpos);
			expo10->setpos(1800, currentexplosionpos);
			shakeScene(GameScene, view, 1, 10);

		}
		if (currentexplosionpos <= -200)
		{
			delete expo1;
			delete expo2;
			delete expo3;
			delete expo4;
			delete expo5;
			delete expo6;
			delete expo7;
			delete expo8;
			delete expo9;
			delete expo10;
			chainetimer->stop();
		}
		});
	chainetimer->start(80);
} 



void explosionmanager::bossdeath()
{
	Sprite* spriteexplosion = new Sprite("boss.png", "boss.json");
	spriteexplosion->setframe(0);
	spriteexplosion->setpos(0, 0);
	spriteexplosion->pixmapItem->setZValue(100);
	spriteexplosion->pixmapItem->setScale(5);
	spriteexplosion->pixmapItem->show();
	GameScene->addItem(spriteexplosion->pixmapItem);
	spriteexplosion->start(35);
	sfxbossdeath.playSFX("bossdeath.wav");
	shakeScene(GameScene, view, 7000, 10);
	flash();
	QTimer::singleShot(6000, [=]() {
		delete spriteexplosion;
		});
	



}

void explosionmanager::flash() {
	flashtimer = new QTimer;
	flashsquare = new QGraphicsRectItem(-10, -10, 2560, 1440);
	flashsquare->setOpacity(0);
	flashsquare->setZValue(300);
	flashsquare->setBrush(Qt::white);
	GameScene->addItem(flashsquare);
	maxbrightness = false;
	
	QObject::connect(flashtimer, &QTimer::timeout, [=]() mutable {
		if (!maxbrightness)
		{
			flashopacity += 0.01;
		}
		
		if (maxbrightness)
		{
			flashopacity -= 0.02;
			//return;
		}
		if (flashopacity > 1.0 && !maxbrightness) 
		{
			maxbrightness = true;
			flashopacity = 1.0;
		}
		flashsquare->setOpacity(flashopacity);
		GameScene->update();
		});
	flashtimer->start(48);
	QTimer::singleShot(11000, [=]() {
		flashtimer->stop();
		//flashopacity = 0;
		//maxbrightness = false;
		delete flashsquare;
		delete flashtimer;
		});
}