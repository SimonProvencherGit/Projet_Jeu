#ifndef JEUBACKGROUND_H
#define JEUBACKGROUND_H
#include "Sprite.h"
#include "globalobjects.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <QRandomGenerator>
class backgroundmanager {
public:
	backgroundmanager();
	void setocean();
	void setforest();
	void setdesert();
	void setspace();
	void bougebackground();
	void stopbackground();
private:
	void eastereggchance();
	int initialback1y = 0;
	int currentback1y = 0;
	int initialback2y = -1284;
	int currentback2y = -1284;
	int easteregg1y = -1284;
	int currenteasteregg1y = -1284;
	int easteregg2y = -1284;
	int currenteasteregg2y = -1284;
	int mapframetimer = 200; // le default pour la map ocean.
	Sprite * Background1;
	Sprite * Background2;
	Sprite* Background3;
	QPixmap* easteregg1image = new QPixmap("Textures\\Scenery\\easter_eg.png");
	QGraphicsPixmapItem* easteregg1;
	QPixmap* easteregg2image = new QPixmap("Textures\\Scenery\\easter_eg2.png");
	QGraphicsPixmapItem* easteregg2;
	QTimer * timerBack1;
	QTimer * timerBack2;
	QTimer* easteregg1timer;
	QTimer* easteregg2timer;


};

class explosionmanager
{
public:
	
	void enemydeathexplosion(int posx,int posy);
	void chainexplosion(int playerposy);
	void bossdeath();
	void flash();
	void shakeScene(QGraphicsScene* scene, QGraphicsView* view, int duration, int magnitude);
private:
	

	bool maxbrightness = false;
	QTimer* flashtimer;
	qreal flashopacity = 0;
	QGraphicsRectItem* flashsquare;
};



#endif
