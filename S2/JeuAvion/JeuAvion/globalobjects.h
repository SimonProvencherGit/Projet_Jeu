#ifndef GLOBALOBJECTS_H
#define GLOBALOBJECTS_H
#include <iostream>
#include <fstream>
#include <string>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QMovie>
#include <QColor>
#include <QTimer>
#include "SFX.h"
#include "Music.h"



// Declare global objects
extern QGraphicsView* view;
extern QGraphicsScene* GameScene;
extern unique_ptr<QPixmap> ListImages[90]; // list global d'images de pixmap. A faire load au debut du jeux
extern bool inspace;
extern void setallSFXVolume(float inputvolume);
extern void savesettings();
extern void loadsettings();
extern SFX sfx;
extern SFX sfxbossdeath;
extern Music music;
extern SFX sfxWarning;
extern SFX enemyexplosion;


#endif 
