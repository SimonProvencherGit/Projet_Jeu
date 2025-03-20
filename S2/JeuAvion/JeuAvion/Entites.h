#ifndef ENTITES_H
#define ENTITES_H

#include <windows.h>    //pour le curseur de la console et sleep()
//#include "Interface.h"
#include "globalobjects.h"
using namespace std;

//definit la taille du jeu
const int WIDTH = 1920;
const int HEIGHT = 1080;
const int CD_BARRELROLL = 75;
const float PI = 3.14159265359;

enum typeEntites { JOUEUR, ENNEMI, OBSTACLE, BULLET, BOSS, POWERUP };
enum typeEnnemis { BASIC, TANK, ARTILLEUR, DIVEBOMBER, ZAPER, AIMBOT, BOSS1_MAIN, BOSS1_SIDE, SIDEBOMBER, BOSS2_MAIN, ORBITER, SHOTGUNHOMING, EXPLODER, TURRET, BOSS3_MAIN, BOSS3_SIDE };
enum typeBullets { NORMAL, LASER, MULTIPLE, HOMING, BOMB, FRAGMENTING, ANGLE, MORTAR, TEMP };
enum typePowerUp { DAMAGEDOUBLED, ADDLIFE, ADDBULLETS };


class Entite
{

public:
    bool flashing = false;
    float posX, posY;
    int xJoueur, yJoueur;
    int  xJoueur2, yJoueur2;
    bool p1EnVie, p2EnVie;
    int largeur, hauteur;
    int xBoss3, yBoss3;
    int shootCooldown;
    int shootTimer;
    bool enVie;
    char symbole;
    int nbVies;
    bool bulletAllie;
    int moveTimer;
    bool collisionJoueur;
    typeEntites typeEntite;
    typeBullets ammoType;
    typePowerUp power_up;
    bool shoots;
    bool invincible;
    int invincibleTimer;
    bool isPlayer;
    int barrelRollTimer = 0;
    // int nbJoueurs;  

    QGraphicsPixmapItem* image;
    QGraphicsPixmapItem* DamageImage;
    QGraphicsPixmapItem* Originalimage;

    Entite(float x, float y, char symb, int longueurEntite, int largeurEntite);
    virtual void update() = 0;
    void perdVie(int nbVie);
    virtual bool enCollision(int px, int py, int larg, int haut);  // retourne vrai si px et py sont egaux au x et y de l'entite
    virtual void getPosJoueurs(float x1, float y1, bool p1Alive, float x2 = 0, float y2 = 0, bool P2Alive = false);
    virtual typeEnnemis getTypeEnnemi();
    virtual void getPosBoss3(float x3, float y3);
};

//-----------------------------------------------------------  classe Joueur -----------------------------------------------------------

class Joueur : public Entite
{
private:
    int attkDmg;
    int vitesse;

public:
    bool barrelRoll;
    int barrelRollTimer;
    int coolDownBarrelRoll;
    int nbBulletTir;

    Joueur(float x, float y);       //probalement autre chose a ajouter
    void update();     //gere le deplacement du joueur
};

//-----------------------------------------------------------  classes Ennemi -----------------------------------------------------------

class Ennemi : public Entite
{
protected:
    int attkDmg;
    int vitesse;
    bool direction;
    int posRand;
    typeEnnemis typeEnnemi;

public:
    Ennemi(float x, float y);
    virtual void update() = 0;     //gere le deplacement de l'ennemi
    typeEnnemis getTypeEnnemi() override;
};

class BasicEnnemi : public Ennemi
{
public:
    BasicEnnemi(float x, float y);
    void update();    //gere le deplacement de l'ennemi

};

class Tank : public Ennemi
{
public:
    Tank(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class DiveBomber : public Ennemi
{
private:
    int joueurRand;
public:
    DiveBomber(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class Artilleur : public Ennemi
{
public:
    Artilleur(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class Zaper : public Ennemi
{
public:
    Zaper(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class Aimbot : public Ennemi
{
public:
    Aimbot(float x, float y);
    void update();
};

class Boss1 : public Ennemi
{
public:
    Boss1(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class Boss1Side : public Ennemi
{
public:
    bool shootTiming;
    bool firstEntry;
    Boss1Side(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class SideBomber : public Ennemi
{
private:
    bool side;
public:
    SideBomber(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class Boss2 : public Ennemi
{
private:
    int rayonMouv;
    int angle;
public:
    Boss2(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};
class Orbiter : public Ennemi
{
private:
    int rayonMouv;
    float distance;
    bool orbiting;
    double angle;
    bool sensRotation;
    int ancrageX = 0;
    int ancrageY = 0;
public:
    Orbiter(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class ShotgunHoming : public Ennemi
{
    ShotgunHoming(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class Exploder : public Ennemi
{
public:
    Exploder(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class Turret : public Ennemi
{
public:
    Turret(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class Boss3 : public Ennemi
{
public:
    Boss3(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};

class Boss3Side : public Ennemi
{
private:
    float rayonMouv;
    float distance;
    bool orbiting;
    double angle;
    bool sensRotation;
    bool changTailleRayon;
public:
    Boss3Side(float x, float y);
    void update();    //gere le deplacement de l'ennemi
};


//-----------------------------------------------------------  classes Bullet -----------------------------------------------------------

class Bullet : public Entite
{
public:

    Bullet(float x, float y, bool isPlayerBullet);
    virtual void update() = 0;   //gere le deplacement de la balle dependant de qui l'a tire on donne la pos x, y du joueur pour les bullets a tete chercheuse
};

class BasicBullet : public Bullet
{
public:
    BasicBullet(float x, float y, bool isPlayerBullet);
    void update() override;    //gere le deplacement de la balle
};

class FragmentingBullet : public Bullet
{
public:
    FragmentingBullet(float x, float y, bool isPlayerBullet);
    void update();    //gere le deplacement de la balle
};

class Laser : public Bullet
{
    
public:
    vector<QGraphicsPixmapItem*> laserSegments;
    Laser(float x, float y, bool isPlayerBullet);
    void update();    //gere le deplacement de la balle
};

class Homing : public Bullet
{
private:
    int joueurRand;
public:
    Homing(float x, float y, bool isPlayerBullet);
    void update();    //gere le deplacement de la balle
};

class angleBullet : public Entite                                              //n'est pas une classe enfant de bullet car a des besoins differents
{
private:
    int direction;
public:
    angleBullet(float x, float y, int angle, char symbole, bool isPlayerBullet);      //direction va de 1 a 8 pour les directions possibles
    void update();    //gere le deplacement de la balle
};

class TempBullet : public angleBullet
{
private:
    int direction;
    int distBullet;
public:
    TempBullet(float x, float y, int angle, bool isPlayerBullet);
    void update();    //gere le deplacement de la balle
};

class Mortar : public Bullet
{
public:
    Mortar(float x, float y, bool isPlayerBullet);
    void update();    //gere le deplacement de la balle
};

//-----------------------------------------------------------  classes Obstacle -----------------------------------------------------------

class Obstacle : public Entite
{
private:
    //int nbVies;

public:
    Obstacle(float x, float y, int longueur, int larg, int vie);
    void update();    //met a jour la vie de l'obstacle
};


//-----------------------------------------------------------  classes PowerUp -----------------------------------------------------------

class PowerUp : public Entite
{
public:
    PowerUp(float x, float y, typePowerUp type);
    virtual void update();
};

class AddLife : public PowerUp
{
public:
    AddLife(float x, float y);
};

class AddBullet : public PowerUp
{
public:
    AddBullet(float x, float y);

};

#endif 