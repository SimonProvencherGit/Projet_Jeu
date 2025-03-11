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

void setConsoleSize();

class Interface
{
private:
    Joueur* joueur;
    Joueur* joueur2;
    vector<unique_ptr<Entite>> bufferBulletsUpdate;  //on fait un buffer pour les bullets pour ne pas les ajouter dans la liste des entites pendant qu'on itere a travers elle
    vector<unique_ptr<Entite>> listEntites;
    //enum tirsAngles{CERCLE,BALAYAGE, RANDOM, RANDOM_CIBLE};
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

public:
    Interface();
    void gererInput();
    void progressionDifficulte();
    void enemySpawn(int nbEnnemi, typeEnnemis enemiVoulu);
    void positionSpawnRandom();
    void updateEntites();
    void updateAffichage();
    void enleverEntites();
    void gererCollisions();
    void executionJeu(int version);
    void hideCursor();
    void showCursor();
    void explosion();
    int cbVivant();
    int customPoints(typeEnnemis);
    void powerupSpawn(int nb, typePowerUp powerUpVoulu, int x, int y);
    //void gererCollisionsPowerUp();
    void restart();
    void cercleTir(int angle, int x, int y);
    void balayageTir(int nbBranches, int vitesseAngulaire, int x, int y);
    void randomTir(int x, int  y);
    void randomCibleTir(int x, int y);
    void joueurTir(Joueur* quelJoueur);
};

#endif // INTERFACE_H