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
	Background2->setframe(1);


	timerBack1 = new QTimer();
	timerBack2 = new QTimer();
	QObject::connect(timerBack1, &QTimer::timeout, [=]() {
		if (currentback1y >= 1284) {
			currentback1y = 0;
			Background1->pixmapItem->setPos(-175, currentback1y);
			GameScene->update();
		}

		Background1->pixmapItem->setPos(-175, currentback1y + 1);
		currentback1y = currentback1y + 1;
		GameScene->update();
		});


	QObject::connect(timerBack2, &QTimer::timeout, [=]() {
		if (currentback2y >= 0) {
			currentback2y = -1284;
			Background2->pixmapItem->setPos(-175, currentback2y);
			GameScene->update();
		}

		Background2->pixmapItem->setPos(-175, currentback2y + 1);
		currentback2y = currentback2y + 1;
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
		GameScene->addItem(Background1->pixmapItem);
		Background2->setpos(-175, -1284);
		Background2->pixmapItem->setScale(0.75);
		Background2->pixmapItem->show();
		GameScene->addItem(Background2->pixmapItem);
		Background2->setframe(1);
		GameScene->update();
		mapframetimer = 100;
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
		Background2->setframe(1);
		GameScene->update();
		mapframetimer = 400;
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
	timerBack1->start(35);
	timerBack2->start(35);


}

void backgroundmanager::stopbackground()
{
	Background1->stop();
	Background2->stop();
	timerBack1->stop();
	timerBack2->stop();
}