#ifndef INTERFACE_H
#define INTERFACE_H

#include "Entites.h"
#include <iostream>
#include <vector>
#include <cstdlib>  //pour rand() et srand()
#include <ctime>    //pour donner point de depart aleatoire a srand() pour la generation de nombres aleatoires
#include <memory>  //pour unique_ptr 
#include <conio.h>  //pour _kbhit()
#include <string>
#include "globalobjects.h"
#include <json.hpp>
#include <Sprite.h>
#include <qdir.h>
#include <QPropertyAnimation>
#include <qparallelanimationgroup.h>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsView>
#include <QThread>
#include <chrono>
#include "JeuBackground.h"
#include "Sprite.h"
#include <QObject>
#include "menu.h"

using json = nlohmann::json;

void setConsoleSize();

class Interface
{
private:
	QGraphicsRectItem* blackBackground;
    Sprite* glitch;
    explosionmanager manageexplosion;
    Sprite* loadExplosion;
    Sprite* loadExplosion2;
    Sprite* loadBarrelRoll;
    Sprite* loadBarrelRoll2;
    //Sprite* rolling;
	//Sprite* rolling2;
    Sprite* Warning;
    Sprite* Water;
    Boss3* boss3;
    Joueur* joueur;
    Joueur* joueur2;
    vector<unique_ptr<Entite>> bufferBulletsUpdate;  //on fait un buffer pour les bullets pour ne pas les ajouter dans la liste des entites pendant qu'on itere a travers elle
    vector<unique_ptr<Entite>> listEntites;
    vector<QGraphicsPixmapItem*> listeNbVie;
	vector<QGraphicsPixmapItem*> listeNbVie2;
    QGraphicsPixmapItem* image;
    backgroundmanager* BackManager;

    QGraphicsPixmapItem* unites;
    QGraphicsPixmapItem* dizaines;
    QGraphicsPixmapItem* centaines;
    QGraphicsPixmapItem* milliers;

    QGraphicsPixmapItem* coeur;
	QGraphicsPixmapItem* coeur2;
	QGraphicsPixmapItem* dixVie;
	QGraphicsPixmapItem* dixVie2;
	QGraphicsPixmapItem* unitVie;
	QGraphicsPixmapItem* unitVie2;
    QGraphicsPixmapItem* x2 = nullptr;

    HANDLE hSerial;


    //enum tirsAngles{CERCLE,BALAYAGE, RANDOM, RANDOM_CIBLE};
    bool firststart = true;
    QTimer tiltresetimerjoueur1; // timer pour remmtre la ou les tilt du joueur a la position initiale
    QTimer tiltresetimerjoueur2;
    void tiltplayerleft(Joueur* player);
    void tiltplayerright(Joueur* player);
    void resettilt(Joueur * Player);

    int score1;
    int score2;
    int scoreTotal;
    bool gameOver;
    int enemySpawnTimer;
    bool pause;
    int posRand;     //pour la position aleatoire de l'ennemi lorsqu'il spawn
    int anciennePos;    //on garde en memoire la position de l'ennemi precedent pour eviter de le spawn a la meme position
    int explosionTimer;
    int explosionPosY;
    bool enExplosion;
    int cdExplosion;
    bool boss1Spawned;
    bool boss2Spawned;
    bool boss3Spawned;
    int bossWaitTimer;      //timer pour attendre un certain temps apres que les ennemis soient morts avant de spawn le boss
    int memScore;
    bool bossMusicStart;
    bool bossSpawnSound;
    int powerUpSpawntimer;
    int angleTirBoss = 0;
    bool spawnAddLife;
    bool spawnPowerUpStart;
    int nbJoueur;

    //bool spawnPowerUp;
    //int nextPup;
    //vector<unique_ptr<PowerUp>> listPowerUps;       //pas besoin de le mettre dans une liste separe, un powerup est un entite et peut etre mis dans la liste d'entites
    int dataManette[7] = { 0 };     //donnes recues de la manette
    int oldDataManette[7] = { 0 };  //donnes precedentes de la manette

public:
    Interface();
    void damageeffect(QGraphicsPixmapItem* pixmapItem, int durationMs, Entite* e);
    void gererInput();
    void progressionDifficulte();
    void enemySpawn(int nbEnnemi, typeEnnemis enemiVoulu);
    void positionSpawnRandom();
    void updateEntites();
    //void updateAffichage();
    void enleverEntites();
    void gererCollisions();
    void executionJeu(int version);
    //void hideCursor();
    //void showCursor();
    void explosion();
    int cbVivant();
    int customPoints(typeEnnemis);
    void powerupSpawn(int nb, typePowerUp powerUpVoulu, int x, int y);
    //void gererCollisionsPowerUp();
    void restart();
    void cercleTir(int angle, int x, int y);
    void cercleExplosion(int angle, int x, int y);
    void balayageTir(int nbBranches, int vitesseAngulaire, int x, int y, int angleStart = 0);
    void randomTir(int x, int  y);
    void randomCibleTir(int x, int y);
    void joueurTir(Joueur* quelJoueur);
    void readSerial(HANDLE hSerial);
    void updateHealthCounter();
    void updateBarrelRollCounter();
    void updateExplosionCounter();
    void updateScore();
	void glitchEffect(bool state);
};

#endif