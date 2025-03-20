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
extern QGraphicsScene* GameScene;
extern QGraphicsPixmapItem* player1;
extern void setallSFXVolume(float inputvolume);
extern void savesettings();
extern void loadsettings();
extern SFX sfx;
extern Music music;
extern SFX sfxWarning;

#endif // GLOBALS_H
