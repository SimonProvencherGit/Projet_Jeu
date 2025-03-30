#ifndef JEUBACKGROUND_H
#define JEUBACKGROUND_H
#include "Sprite.h"
#include "globalobjects.h"
#include <QTimer>
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
	int initialback1y = 0;
	int currentback1y = 0;
	int initialback2y = -1284;
	int currentback2y = -1284;
	int mapframetimer = 150; // le default pour la map ocean.
	Sprite * Background1;
	Sprite * Background2;
	Sprite* Background3;
	QTimer * timerBack1;
	QTimer * timerBack2;


};

#endif
