#include "Interface.h"
#include <qdir.h>
#include <QPropertyAnimation>
#include <qparallelanimationgroup.h>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsView>
#include <QThread>
#include <chrono>
bool firststart = true;

QThread EffectThread;

void shakeScene(QGraphicsScene* scene, QGraphicsView* view, int duration, int magnitude) {
    QRectF originalScene = scene->sceneRect();
    QTimer* timer = new QTimer(view); 
    int elapsed = 0;

    QObject::connect(timer, &QTimer::timeout, [=]() mutable {
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


void Interface::damageeffect(QGraphicsPixmapItem* pixmapItem, int durationMs, Entite* e) {
    auto start = std::chrono::high_resolution_clock::now();
    if (e->enVie == false)
    {
        return;
    }
    if (e->flashing == true)
    {
        return;
    }
    
    
    QPixmap originalPixmap = pixmapItem->pixmap();

   
    pixmapItem->setPixmap(e->DamageImage->pixmap());
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    qDebug() << "Execution time: " << duration << " ms";
   //Retourner l'image a l'originale
    QTimer::singleShot(durationMs, [pixmapItem, originalPixmap, e]() {
        
        if (e->enVie == true) {
             
           
           if (pixmapItem == nullptr)
           {
               return;
           }
          try{
              QPixmap revertpix = e->Originalimage->pixmap();
          e->image->setPixmap(revertpix);
          }
          catch(...)
          {
              qDebug() << "Failed to revert image";
           // erreur
          }
          e->flashing = false;
       }
        });
}



Interface::Interface()
{
    //initialisation des vairalbes
    score1 = 0;
    score2 = 0;
    scoreTotal = 0;
    gameOver = false;
    enemySpawnTimer = 0;
    pause = false;
    posRand = 0;
    anciennePos = 0;
    explosionTimer = 0;
    enExplosion = false;
    explosionPosY = 0;
    cdExplosion = 0;
    boss1Spawned = false;
    boss2Spawned = false;
    bossWaitTimer = 0;
    memScore = 1200;
    bossMusicStart = false;
    bossSpawnSound = false;
    powerUpSpawntimer = 0;
    angleTirBoss = 0;
    spawnAddLife = false;
    spawnPowerUpStart = true;      //temporaire pour faire spawn powerup au debut du match
    nbJoueur = 1;
    //nextPup = 0;

    listEntites.emplace_back(make_unique<Joueur>(WIDTH / 2, HEIGHT));   //ajoute le joueur a la liste d'entites
    //listEntites.emplace_back(make_unique<Joueur>(0, 0));
    joueur = static_cast<Joueur*>(listEntites.back().get());                //on recupere le * du joueur de la liste d'entites
    joueur->posY = HEIGHT - joueur->hauteur;
    joueur2 = nullptr;
}


//gere les inputs du joueur
void Interface::gererInput()
{
    if (pause == false)
    {

        if (GetAsyncKeyState('A') < 0)   //on verifie si la fleche gauche ou D est pressee
        {
            if (joueur->posX > -1)
            {
                if (joueur->posX < 10)
                {
					joueur->posX = joueur->posX - joueur->posX;         //wtf is this line
                }
                else
                joueur->posX -= 10;      //on deplace le joueur de 2 vers la gauche
            }
            else if (joueur->posX  <-1)
                joueur->posX-=10;
        }
        if (GetAsyncKeyState('D') < 0) {
            if (joueur->posX < WIDTH-joueur->largeur)
                joueur->posX += 10;
        }

        if (GetAsyncKeyState('W') < 0)
            if (joueur->posY > 0)      //le joueur a acces au 9/10 de l'ecran
                joueur->posY -= 10;

        if (GetAsyncKeyState('S') < 0)
            if (joueur->posY < HEIGHT - joueur->hauteur)      //le joueur a acces au 9/10 de l'ecran
                joueur->posY += 10;

        if (GetAsyncKeyState(VK_SPACE) < 0)
        {
            if (joueur->shootTimer == 0 && joueur->barrelRollTimer <= 0)    //on tire si on peut
            {
                //listEntites.emplace_back(make_unique<BasicBullet>(joueur->posX + joueur->largeur / 2, joueur->posY - 1, true));
                joueurTir(joueur);
                joueur->shootTimer = joueur->shootCooldown;   //on reset le cooldown de tir du joueur pour que update puisse le faire baisser a chaque frame pour pouvoir retirer

            }
        }
        if (GetAsyncKeyState('E') < 0)
        {
            if (joueur->barrelRoll == false && joueur->coolDownBarrelRoll <= 0)
                joueur->barrelRoll = true;
        }
        if (GetAsyncKeyState('R') < 0)
        {
            if (explosionTimer == 0)
            {
                cdExplosion = 500;      //set le cooldown de l'explosion
                enExplosion = true;
                explosionTimer = cdExplosion;
                explosionPosY = joueur->posY - 1;
                shakeScene(GameScene, view, 1000, 10);
            }
        }

        //******************************************* controle 2e joueur *******************************************
        if (nbJoueur > 1)
        {
            if (GetAsyncKeyState(VK_LEFT) < 0)   //on verifie si la fleche gauche ou D est pressee
            {
                if (joueur2->posX > 2)
                    joueur2->posX -= 2;      //on deplace le joueur de 2 vers la gauche
                else if (joueur2->posX > 1)
                    joueur2->posX--;
            }
            if (GetAsyncKeyState(VK_RIGHT) < 0) {
                if (joueur2->posX < WIDTH - 2)
                    joueur2->posX += 2;
                else if (joueur2->posX < WIDTH - 1)
                    joueur2->posX++;
            }

            if (GetAsyncKeyState(VK_UP) < 0)
                if (joueur2->posY > HEIGHT / 10)      //le joueur a acces au 9/10 de l'ecran
                    joueur2->posY--;

            if (GetAsyncKeyState(VK_DOWN) < 0)
                if (joueur2->posY < HEIGHT)
                    joueur2->posY++;
            if (GetAsyncKeyState(VK_INSERT) < 0)       // touche controle pour tirer pour ce joueur, mais ca va changer qd la manette va etre implementee
            {
                if (joueur2->shootTimer == 0 && joueur2->barrelRollTimer <= 0)    //on tire si on peut
                {
                    //listEntites.emplace_back(make_unique<BasicBullet>(joueur->posX + joueur->largeur / 2, joueur->posY - 1, true));
                    joueurTir(joueur2);
                    joueur2->shootTimer = joueur2->shootCooldown;   //on reset le cooldown de tir du joueur pour que update puisse le faire baisser a chaque frame pour pouvoir retirer

                }
            }
            if (GetAsyncKeyState(VK_DELETE) < 0)
            {
                if (joueur2->barrelRoll == false && joueur2->coolDownBarrelRoll <= 0)
                    joueur2->barrelRoll = true;
            }
            if (GetAsyncKeyState(VK_END) < 0)
            {
                if (explosionTimer == 0)
                {

                    cdExplosion = 500;      //set le cooldown de l'explosion
                    enExplosion = true;
                    explosionTimer = cdExplosion;
                    explosionPosY = joueur2->posY - 1;
                }
            }
        }


        if (explosionTimer > 0)
        {
            explosionTimer--;
            explosion();
        }
    }
    if (GetAsyncKeyState('Q') < 0)
        gameOver = true;

    if (GetAsyncKeyState('P') < 0)
    {
        if (pause)
            pause = false;
        else if (!pause)
            pause = true;
        Sleep(200);
    }
}
void Interface::joueurTir(Joueur* quelJoueur)
{
   /* QMovie* basicbullet = new QMovie("Textures\\bullets\\basicbullet.gif");
    basicbullet->start();
    QLabel* labelbasicbullet = new QLabel;
    labelbasicbullet->setMovie(basicbullet);
    labelbasicbullet->move(1, 2);*/
    switch (quelJoueur->nbBulletTir)
    {
    case 1:
        listEntites.emplace_back(make_unique<angleBullet>(quelJoueur->posX + quelJoueur->largeur / 2, quelJoueur->posY - 1, 90 + 180, '|', true));
        break;
    case 3:
        for (int i = 80;i < 110;i += 10)
            listEntites.emplace_back(make_unique<angleBullet>(quelJoueur->posX + quelJoueur->largeur / 2, quelJoueur->posY - 1, i + 180, '|', true));
        break;
    case 5:
        for (int i = 70; i < 120; i += 10)
            listEntites.emplace_back(make_unique<angleBullet>(quelJoueur->posX + quelJoueur->largeur / 2, quelJoueur->posY - 1, i + 180, '|', true));
        break;
    }
}


void Interface::explosion()
{

    if (enExplosion)
    {
        for (auto& e : listEntites)
        {
            if (e->enVie && e->posY >= explosionPosY - 2 && e->posY <= explosionPosY + 2 && !e->isPlayer && e->typeEntite != BOSS && e->typeEntite != POWERUP)	//on verifie si l'entite est dans une zone d'explosion qui avance vers le haut de l'ecran
            {
                e->enVie = false;
                //score += customPoints(e->getTypeEnnemi());
            }
        }
    }

    if (explosionPosY > 0)
        explosionPosY-=5;
    else
        enExplosion = false;
}

int Interface::cbVivant()
{
    int nbVivant = 0;

    for (auto& e : listEntites)
    {
        if (e->enVie == true && (e->typeEntite == ENNEMI || e->typeEntite == BOSS))
            nbVivant++;
    }
    return nbVivant;
}




//fait spawn x nb d'ennemis
void Interface::enemySpawn(int nbEnnemi, typeEnnemis ennemiVoulu)
{
    posRand = (rand() % (WIDTH)) + 1;
    int coterand;
    for (int i = 0; i < nbEnnemi; i++)  //on fait spawn un nombre d'ennemis egal a nbEnnemi
    {
        //anciennePos = posRand;

        switch (ennemiVoulu)
        {
        case BASIC:
            listEntites.emplace_back(make_unique<BasicEnnemi>(posRand, 0));
            positionSpawnRandom();
            break;
        case TANK:
            listEntites.emplace_back(make_unique<Tank>(posRand, 0));
            positionSpawnRandom();
            break;
        case ARTILLEUR:
            listEntites.emplace_back(make_unique<Artilleur>(posRand, 0));
            positionSpawnRandom();
            break;
        case DIVEBOMBER:
            listEntites.emplace_back(make_unique<DiveBomber>(posRand, 0));
            positionSpawnRandom();
            break;
        case ZAPER:
            listEntites.emplace_back(make_unique<Zaper>(posRand, 0));
            positionSpawnRandom();
            break;
        case AIMBOT:
            listEntites.emplace_back(make_unique<Aimbot>(posRand, 0));
            positionSpawnRandom();
            break;
        case BOSS1_MAIN:
            listEntites.emplace_back(make_unique<Boss1>(WIDTH / 3, 0));
            listEntites.emplace_back(make_unique<Boss1Side>(WIDTH - WIDTH / 6, 4));
            listEntites.emplace_back(make_unique<Boss1Side>(WIDTH / 6, 4));
            listEntites.emplace_back(make_unique<Boss1Side>(WIDTH / 2, 4));
            break;
        case SIDEBOMBER:
            coterand = rand() % 2;
            if (coterand == 0)
                listEntites.emplace_back(make_unique<SideBomber>(WIDTH - 1, (rand() % (HEIGHT - 2)) + 1));          //on fait spawn un ennemi a une position aleatoire en y, la position en x de WIDTH - 2 se fait changer dans le constructeur dependant du sens de l'ennemi
            else
                listEntites.emplace_back(make_unique<SideBomber>(1, (rand() % (HEIGHT - 2)) + 1));          //on fait spawn un ennemi a une position aleatoire en y, la position en x de 1 se fait changer dans le constructeur dependant du sens de l'ennemi
            break;
        case BOSS2_MAIN:
            listEntites.emplace_back(make_unique<Boss2>(WIDTH / 2, HEIGHT / 3));
            break;
        case SHOTGUNNER:
            listEntites.emplace_back(make_unique<Shotgunner>(posRand, 0));
            positionSpawnRandom();
            break;
        }
    }
}

void Interface::powerupSpawn(int nb, typePowerUp powerUpVoulu, int x, int y)
{
    for (int i = 0; i < nb; i++)
    {
        switch (powerUpVoulu)
        {

        case ADDLIFE:
            listEntites.emplace_back(make_unique<AddLife>(x, y));
            break;

        case ADDBULLETS:
            listEntites.emplace_back(make_unique<AddBullet>(x, y));
            break;
        }
    }
}


void Interface::positionSpawnRandom()       //on donne une position aleatoire a l'ennemi au spawn en evitant qu'il spawn avec une partie de lui hors de l'ecran
{
    posRand = (rand() % (WIDTH - listEntites.back()->largeur - 1)) + 1;     //on genere une position aleatoire pour l'ennemi + 1 pour ne pas etre sur la bordure
    anciennePos = posRand;
    while (posRand == anciennePos)	  //on s'assure que le nouvel ennemi n'est pas a la meme position que le dernier
        posRand = (rand() % (WIDTH - listEntites.back()->largeur - 1)) + 2;

    listEntites.back()->posX = posRand;
}


void Interface::progressionDifficulte()
{
    enemySpawnTimer++;
    static bool spawnPup = false;

    if (score1 < 600)
    {

        if (enemySpawnTimer >= 200 || cbVivant() < 6)          //on fait spawn une vague d'ennemis a toutes les 70 frames
       // if (enemySpawnTimer >= 100) //pour des tests
       {
            enemySpawn(1, BASIC);   //on fait spawn 3 ennemis a chaque vague
            enemySpawn(1, ARTILLEUR);
            //enemySpawn(1, ZAPER);
            //enemySpawn(1, AIMBOT);
            //enemySpawn(2, SIDEBOMBER);
            enemySpawn(1, DIVEBOMBER);
            //enemySpawn(1, TANK);
            //enemySpawn(1, SHOTGUNNER);

            if (spawnPowerUpStart)
            {
                spawnPowerUpStart = false;
                powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2 - 70);
                powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2);
            }
            enemySpawnTimer = 0;        //on reset le timer pour pouvoir spanw la prochaine vague d'ennemis
       }
    }
    if (score1 >= 600 && score1 < 1300)
    {
        if (enemySpawnTimer >= 50)          //on fait spawn une vague d'ennemis a toutes les 60 frames
        {
            //enemySpawn(3, BASIC);   //on fait spawn 4 ennemis a chaque vague
            enemySpawn(5, DIVEBOMBER);
            enemySpawnTimer = 0;        //on reset le timer pour pouvoir spanw la prochaine vague d'ennemis
        }
    }
    if (score1 >= 1300 && score1 < 2000)
    {
        if (enemySpawnTimer >= 150 || cbVivant() < 4)          //on fait spawn une vague d'ennemis a toutes les 50 frames
        {
            //enemySpawn(1, ARTILLEUR);
            //enemySpawn(4, BASIC);   //on fait spawn 5 ennemis a chaque vague
           // enemySpawn(2, DIVEBOMBER);
            enemySpawn(2, AIMBOT);

            int nbTank = 0;

            for (auto& e : listEntites)
            {
                if (e->getTypeEnnemi() == TANK)
                    nbTank++;
            }
            if (nbTank < 2)
                enemySpawn(1, TANK);

            enemySpawnTimer = 0;        //on reset le timer pour pouvoir spanw la prochaine vague d'ennemis
        }
    }
    if (score1 >= 2000 && !boss1Spawned)
    {
        if (cbVivant() == 0)
        {
            if (!bossMusicStart && !bossSpawnSound)
            {
                music.stopMusic();
                sfxWarning.playSFX("warning.wav");
                bossSpawnSound = true;
                enemySpawnTimer = 0;
                //Sleep(5);
            }
            else if (!bossMusicStart && bossSpawnSound)
            {

                if (enemySpawnTimer >= 125)         //
                {
                    sfxWarning.stopSFX();
                    music.playMusic("Boss1.wav", 0, 100000);
                    bossMusicStart = true;

                }
            }

            if (bossWaitTimer > 200)	 //on attend un certain temps apres la mort du dernier ennemi avant de spawn le boss
            {
                enemySpawn(1, BOSS1_MAIN);
                boss1Spawned = true;

                memScore = score1 + 200;     //on garde le score en memoire lorsque le boss apparait, on y ajoute 250 pour le score du boss afin de connaitre le score qd le boss meurt afin de faire apparaitre les prochains ennemis
                bossWaitTimer = 0;
            }
            else
                bossWaitTimer++;
        }
    }
    if (score1 >= memScore && score1 <= memScore + 850 && boss1Spawned)   //on fait spawn des ennemis apres que le boss soit mort 
    {

        if (bossWaitTimer > 100)
        {
            if (enemySpawnTimer >= 150 || cbVivant() < 7)
            {
                enemySpawn(4, SIDEBOMBER);
                enemySpawn(1, AIMBOT);
                enemySpawn(1, ZAPER);
                enemySpawnTimer = 0;

            }
        }
        else
            bossWaitTimer++;
    }
    if (score1 >= memScore + 850 && score1 <= memScore + 1600 && boss1Spawned)   //on fait spawn des ennemis apres que le boss soit mort 
    {
        if (enemySpawnTimer >= 5)
        {
            enemySpawn(1, DIVEBOMBER);
            enemySpawnTimer = 0;
            bossWaitTimer = 0;
        }
    }
    if (score1 >= memScore + 1600 && score1 <= memScore + 2400 && boss1Spawned)
    {
        if (enemySpawnTimer >= 150 || cbVivant() < 8)
        {
            enemySpawn(1, ARTILLEUR);
            enemySpawn(1, SIDEBOMBER);
            enemySpawn(1, TANK);
            enemySpawn(1, AIMBOT);
            enemySpawn(1, ZAPER);
            enemySpawn(1, DIVEBOMBER);
            enemySpawn(1, BASIC);
            enemySpawnTimer = 0;
        }
    }
    if (score1 >= memScore + 2400 && !boss2Spawned)
    {
        if (cbVivant() == 0)
        {

            if (bossWaitTimer > 200)	 //on attend un certain temps apres la mort du dernier ennemi avant de spawn le boss
            {
                enemySpawn(1, BOSS2_MAIN);
                boss2Spawned = true;

                memScore = score1 + 200;     //on garde le score en memoire lorsque le boss apparait, on y ajoute 250 pour le score du boss afin de connaitre le score qd le boss meurt afin de faire apparaitre les prochains ennemis
                bossWaitTimer = 0;
            }
            else
                bossWaitTimer++;
        }
    }
}


//met a jour les entites a chaque frame
void Interface::updateEntites()
{
    for (auto& e : listEntites)     //on parcourt la liste d'entites
    {
        if (e->enVie)
        {
            if (nbJoueur == 1)
                e->getPosJoueurs(joueur->posX, joueur->posX, joueur->enVie);   //on donne la position du joueur a chaque entite, va etre utliser pour les choses a tete chercheuse etc.
            
            else if (nbJoueur == 2)
            {
                if ((joueur->posX < 0 || joueur->posY < 0) && joueur2->posX >= 0 && joueur2->posY >= 0)       //si le joueur 1 est mort et le joueur 2 est en vie
                    e->getPosJoueurs(-1, -1, false, joueur2->posX, joueur2->posY, joueur2->enVie);
                else if ((joueur2->posX < 0 || joueur2->posY < 0) && joueur->posX >= 0 && joueur->posY >= 0)       //si le joueur 2 est mort et le joueur 1 est en vie
                    e->getPosJoueurs(joueur->posX, joueur->posY, joueur->enVie, -1, -1, false);
                else if (joueur->posX >= 0 && joueur->posY >= 0 && joueur2->posX >= 0 && joueur2->posY >= 0)       //si les 2 joueurs sont en vie
                    e->getPosJoueurs(joueur->posX, joueur->posX, joueur->enVie, joueur2->posX, joueur2->posY, joueur2->enVie);
            }

            e->update();    //on met a jour chaque entite

            if (e->typeEntite == ENNEMI && e->ammoType == NORMAL && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //on verifie si c'est un ennemi et si sont compteur pour tirer est a 0
                bufferBulletsUpdate.emplace_back(make_unique<BasicBullet>(e->posX + e->largeur / 2, e->posY + e->hauteur + 1, false));     //on cree un bullet a la position de l'ennemi qu'on met un buffer temporaire pour eviter de les ajouter a la liste d'entites pendant qu'on itere a travers d'elle  

            if (e->typeEntite == ENNEMI && e->ammoType == FRAGMENTING && e->moveTimer % e->shootCooldown == 0 && e->shoots)     //si c'est un ennemi qui tire des fragmenting bullets
                bufferBulletsUpdate.emplace_back(make_unique<FragmentingBullet>(e->posX + e->largeur / 2, e->posY + e->hauteur + 1, false));

            if ((e->typeEntite == ENNEMI || e->typeEntite == BOSS) && e->ammoType == LASER && e->moveTimer % e->shootCooldown == 0 && e->shoots)	//si c'est un ennemi qui tire des lasers
                bufferBulletsUpdate.emplace_back(make_unique<Laser>(e->posX + e->largeur / 2, e->posY + e->hauteur, false));

            if (e->getTypeEnnemi() == AIMBOT && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //si c'est un ennemi qui tire des missiles tete chercheuse
                bufferBulletsUpdate.emplace_back(make_unique<Homing>(e->posX + e->largeur / 2, e->posY + e->hauteur + 1, false));


            if (e->getTypeEnnemi() == BOSS1_MAIN && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //si c'est le boss1 tire des 3 missiles
            {
                bufferBulletsUpdate.emplace_back(make_unique<Homing>(e->posX + e->largeur / 4, e->posY + e->hauteur + 1, false));
                bufferBulletsUpdate.emplace_back(make_unique<Homing>(e->posX + e->largeur - e->largeur / 4, e->posY + e->hauteur + 1, false));
                bufferBulletsUpdate.emplace_back(make_unique<Homing>(e->posX + e->largeur / 2, e->posY + e->hauteur + 1, false));
            }

            if (e->getTypeEnnemi() == BOSS1_MAIN)    //verifie si c'est le main boss pour faire qu'il est invincible si on a pas tuer ces side boss
            {
                e->invincible = false;

                for (auto& e2 : listEntites)
                {
                    if (e2->enVie == true && e2->getTypeEnnemi() == BOSS1_SIDE)
                    {
                        e->invincible = true;
                    }
                }
            }

            if (e->getTypeEnnemi() == BOSS2_MAIN && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //si c'est le 2e boss
            {
                if (e->nbVies % 70 == 0 && spawnAddLife)
                {
                    powerupSpawn(1, ADDLIFE, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                    spawnAddLife = false;
                }
                else if (e->nbVies % 70 != 0)
                    spawnAddLife = true;

                if (e->moveTimer % 2 == 0)
                    randomCibleTir(e->posX + e->largeur / 2, e->posY + e->hauteur / 2);

                if (e->nbVies >= 140)
                {
                    if (e->moveTimer % 90 == 0)
                        cercleTir(25, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);

                    balayageTir(4, 2, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);

                }
                else if (e->nbVies < 140 && e->nbVies >= 70)
                {
                    balayageTir(4, 26, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                }
                else if (e->nbVies < 70)
                {
                    if (e->moveTimer % 100 == 0)
                        cercleTir(5, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);

                    balayageTir(5, 1, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                }
                angleTirBoss += 5;
                if (angleTirBoss >= 360)
                    angleTirBoss = 0;
            }
        }
    }
    for (auto& bullet : bufferBulletsUpdate)
    {
        if (bullet != nullptr)
            listEntites.push_back(move(bullet));	//on ajoute les bullets du buffer a la liste d'entites
    }
}


void Interface::cercleTir(int angle, int x, int y)
{
    for (int i = 0; i <= 360; i += angle)
        bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(x, y, i, 'o', false));
}

void Interface::balayageTir(int nbBranches, int vitesseAngulaire, int x, int y)
{
    for (int i = 0; i < 360; i += 360 / nbBranches)
        bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(x, y, angleTirBoss + i, 'o', false));

    angleTirBoss += vitesseAngulaire;
    if (angleTirBoss >= 360)
        angleTirBoss = 0;
}

void Interface::randomTir(int x, int  y)
{
    int randPos = rand() % 360;
    bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(x, y, randPos, 'o', false));
}

void Interface::randomCibleTir(int x, int y)
{
    //calcule l'angle entre le joueur et le boss et tire aleatoirement dans un cone de 40 degres vers le joueur
    int dx = joueur->posX - x;
    int dy = joueur->posY - y;
    double angle = atan2(dy, dx) * 180 / 3.14159265;     //retourne l'angle en degres entre le boss et le joueur         https://www.w3schools.com/cpp/ref_math_atan2.asp
    int randPos = rand() % 40;      //correspond a une variation possible de 40 degres
    bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(x, y, angle - 20 + randPos, 'o', false));         //on tire aleatoirement dans un cone de 40 degres vers le joueur
}



//gere les collisions entre les entites
void Interface::gererCollisions()
{
    vector<unique_ptr<Entite>> bufferBullets;  //on fait un buffer pour les bullets car on ne peut pas ajouter a la liste entite pendant qu`on itere a travers
    static int scoreLastPup = 0;

    for (auto& e : listEntites)
    {
        if (e->enVie)
        {
            if (e->enCollision(joueur->posX, joueur->posY, joueur->largeur, joueur->hauteur) && joueur->invincibleTimer <= 0 && joueur->barrelRollTimer <= 0 && !e->isPlayer)     //on verifie si un entite entre en collision avec le joueur et verifie que e n'est pas joueur
            {
                if ((e->typeEntite == ENNEMI || e->typeEntite == BOSS) && e->collisionJoueur == false)
                {
                    joueur->perdVie(2);	 //le joueur perd 2 vies si il entre en collision avec un ennemi
                    joueur->invincible = true;     //le joueur est invincible pour un court moment apres
                    damageeffect(joueur->image, 100, joueur);
                    //if(!joueur->enVie)
                        //nbJoueur--;
                        //gameOver = true;

                    e->collisionJoueur = true;
                }
                else if (e->typeEntite == BULLET && e->collisionJoueur == false && !e->bulletAllie)     //si le joueur entre en collision avec une bullet ennemi sans etre en barrel roll il perd une vie
                {
                    joueur->perdVie(1);    //le joueur perd 1 vie si il entre en collision avec une bullet ennemi et s'il est pas invincible
                    joueur->invincible = true;     //le joueur est invincible pour un court moment apres

                    //if (!joueur->enVie)
                        //nbJoueur--;
                        //gameOver = true;
                    damageeffect(joueur->image, 100, joueur);
                    e->collisionJoueur = true;
                }
                else if (e->typeEntite == POWERUP)	//si le joueur entre en collision avec un powerup
                {
                    switch (e->power_up)        //on verifie quel type de powerup c'est pour faire les actions appropriees
                    {
                    case ADDLIFE:
                        joueur->nbVies++;
                        break;

                    case ADDBULLETS:
                        joueur->nbBulletTir += 2;
                        joueur->shootCooldown += 3;
                        break;
                    }
                    e->enVie = false;
                }
            }
            //partie ou on gere les collision avec les bullets alliees
            else if (e->typeEntite == BULLET && e->bulletAllie)  //on verifie si c'est un bullet allie tire par le joueur
            {
                for (auto& e2 : listEntites)	//on parcourt la liste d'entites pour voir si la bullet entre en collision avec un ennemi
                {
                    if (e2->enVie)
                    {
                        if (e2->enVie && e2->enCollision(e->posX, e->posY, e->largeur, e->hauteur) && e2->symbole != e->symbole && e2->typeEntite != POWERUP && !e2->isPlayer)       // si qqlch entre en collision avec la bullet allie et le e->symbole est pour pas que la bullet entre en collision avec elle meme 
                        {
                            if (e2->ammoType == FRAGMENTING && e2->typeEntite == BULLET && !e2->bulletAllie)      //si c'est un fragmenting bullet d'unennemi
                                for (int i = -1; i < 2; i++)	//commence a -1 pour que le premier fragment commence a la gauche de la bullet
                                    bufferBullets.emplace_back(make_unique<BasicBullet>(e2->posX + i, e2->posY + 1, false));

                            e2->perdVie(1);
                            damageeffect(e2->image, 100, e2.get());
                            if (e2->nbVies != 0)       //si l'ennemi n'a pas de vie comme
                                e->enVie = false;   //la bullet meurt si elle entre en collision avec un ennemi

                            if (!e2->enVie && (e2->typeEntite == ENNEMI || e2->typeEntite == BOSS))
                            {

                                score1 += customPoints(e2->getTypeEnnemi());
                                if (score1 % 500 <= 10 && score1 > 100 && score1 > scoreLastPup + 50)        //on fait spawn un powerup a chaque 500 points.  le scoreLastPup sert a ne pas faire spawn 2 pup back to back parfois
                                {
                                    powerupSpawn(1, ADDLIFE, e2->posX + e2->largeur / 2, e2->posY + e2->hauteur / 2);       //on fait spawn un powerup a la position de l'ennemi
                                    scoreLastPup = score1;
                                }
                                if (e2->typeEntite == BOSS)
                                    powerupSpawn(1, ADDLIFE, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                            }
                        }
                    }
                }
            }
            else
                e->collisionJoueur = false;
        }

        if (nbJoueur > 1)       //s'il y a 2 joueur 
        {
            if (e->enVie)
            {
                if (e->enCollision(joueur->posX, joueur->posY, joueur->largeur, joueur->hauteur) && joueur2->invincibleTimer <= 0 && joueur2->barrelRollTimer <= 0 && !e->isPlayer)     //on verifie si un entite entre en collision avec le joueur et verifie que e n'est pas joueur
                {
                    if ((e->typeEntite == ENNEMI || e->typeEntite == BOSS) && e->collisionJoueur == false)
                    {
                        joueur2->perdVie(2);	 //le joueur perd 2 vies si il entre en collision avec un ennemi
                        joueur2->invincible = true;     //le joueur est invincible pour un court moment apres

                        //if (!joueur2->enVie)
                            //nbJoueur--;
                            //gameOver = true;

                        e->collisionJoueur = true;
                    }
                    else if (e->typeEntite == BULLET && e->collisionJoueur == false && !e->bulletAllie)     //si le joueur entre en collision avec une bullet ennemi sans etre en barrel roll il perd une vie
                    {
                        joueur2->perdVie(1);    //le joueur perd 1 vie si il entre en collision avec une bullet ennemi et s'il est pas invincible
                        joueur2->invincible = true;     //le joueur est invincible pour un court moment apres

                        //if (!joueur2->enVie)        //----------------------------------------------------------------------------------------  a changer, si un des 2 joueurs meurt en ce moment la game finit
                            //nbJoueur--;
                            //gameOver = true;

                        e->collisionJoueur = true;
                    }
                    else if (e->typeEntite == POWERUP)	//si le joueur entre en collision avec un powerup
                    {
                        switch (e->power_up)        //on verifie quel type de powerup c'est pour faire les actions appropriees
                        {
                        case ADDLIFE:
                            joueur2->nbVies++;
                            break;

                        case ADDBULLETS:
                            joueur2->nbBulletTir += 2;
                            joueur2->shootCooldown += 3;
                            break;
                        }
                        e->enVie = false;
                    }
                }
                else
                    e->collisionJoueur = false;
            }
        }
    }
    for (auto& bullet : bufferBullets)
        listEntites.push_back(move(bullet));	//on ajoute les bullets du buffer a la liste d'entites
}

int Interface::customPoints(typeEnnemis e)
{
    switch (e)
    {
    case BASIC:
        return 10;
        break;
    case TANK:
        return 20;
        break;
    case ARTILLEUR:
        return 25;
        break;
    case DIVEBOMBER:
        return 20;
        break;
    case ZAPER:
        return 30;
        break;
    case AIMBOT:
        return 30;
        break;
    case BOSS1_MAIN:
        music.playMusic("Forest.wav", 21639, 115195);
        powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2);
        return 100;
        break;
    case BOSS1_SIDE:
        return 50;
        break;
    case SIDEBOMBER:
        return 15;
        break;
    case BOSS2_MAIN:
        powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2);
        return 300;
    }
    return 0;
}

void Interface::restart()
{
    for (auto& e : listEntites)
        e->enVie = false;

    gameOver = false;
    listEntites.emplace_back(make_unique<Joueur>(WIDTH / 2, HEIGHT - 1));   //ajoute le joueur a la liste d'entites
    joueur = static_cast<Joueur*>(listEntites.back().get());
    score1 = 0;
    explosionTimer = 0;
    enExplosion = false;
    cdExplosion = 0;
    boss1Spawned = false;
    bossWaitTimer = 0;
    memScore = 1200;
    bossMusicStart = false;
    bossSpawnSound = false;
    spawnAddLife = true;
    spawnPowerUpStart = true;
}


//met a jour l'affichage de la console 
void Interface::updateAffichage()
{
   /* wchar_t buffer[HEIGHT + 5][WIDTH + 2];  // +3 pour les bordures et le score, +2 pour les bordures
    wchar_t progressExplosion[12];	//buffer pour afficher progression de l'explosion
    wchar_t progressBarrelRoll[12];	//buffer pour afficher progression du barrel roll
    float nbSymboleExplosion = 0;  //pour le nombre de symboles a afficher dans la progression de l'explosion
    float nbSymboleBarrelRollP1 = 0;
    float nbSymboleBarrelRollP2 = 0;
    wstring texte;  //on cree un string pour afficher le score, le nombre de vies et autres textes


    // Remplir le tampon avec des espaces (effacer l'écran)
    for (int y = 0; y < HEIGHT + 5; y++) {
        for (int x = 0; x < WIDTH + 2; x++) {
            buffer[y][x] = L' ';
        }
    }

    //rempli le buffer progressexplosion avec des espaces
    for (int i = 0; i < 12; i++)
        progressExplosion[i] = L' ';

    //rempli le buffer progressBarrelRoll avec des espaces
    for (int i = 0; i < 12; i++)
        progressBarrelRoll[i] = L' ';


    // Mettre à jour les bordures
    for (int x = 0; x < WIDTH + 2; x++)     //on met les bordures du haut et du bas
    {
        buffer[0][x] = L'#';
        buffer[HEIGHT + 1][x] = L'#';
    }
    for (int y = 1; y <= HEIGHT; y++)   //on met les bordures de gauche et de droite, on commence a 1 et finit a HEIGHT pour pas ecraser les bordures du haut et du bas
    {
        buffer[y][0] = L'#';
        buffer[y][WIDTH + 1] = L'#';
    }

    // Mettre à jour les entités vivantes
    for (auto& e : listEntites)
    {
        if (e->enVie)
        {
            for (int y = 0; y < e->hauteur; y++)        //on parcourt la hauteur de l'entite
            {
                for (int x = 0; x < e->largeur; x++)    //on parcourt la largeur de l'entite
                {
                    buffer[(int)e->posY + y][(int)e->posX + x] = e->symbole;  //on met a jour la position de l'entite dans le buffer
                }
            }
        }
    }

    //Affiche progression pour l'explosion
    progressExplosion[0] = L'[';
    progressExplosion[11] = L']';

    if (explosionTimer == 0)
        nbSymboleExplosion = 10;
    else
        nbSymboleExplosion = ((float)(cdExplosion - explosionTimer) / (float)cdExplosion) * 10;

    for (int i = 0; i < (int)nbSymboleExplosion; i++)
        progressExplosion[i + 1] = L'#';

    texte = L"Explosion: ";
    for (int i = 0; i < texte.size(); i++)   //on ajoute le score au buffer
        buffer[HEIGHT + 2][i] = texte[i];

    for (int i = 0; i < 12; i++)
        buffer[HEIGHT + 2][i + texte.size()] = progressExplosion[i];

    //Affiche progression pour le barrel roll
    progressBarrelRoll[0] = L'[';
    progressBarrelRoll[11] = L']';
    int posCurseur = 12 + texte.size() + 5;

    if (joueur->coolDownBarrelRoll == 0)
        nbSymboleBarrelRollP1 = 10;
    else
    {
        nbSymboleBarrelRollP1 = ((float)(CD_BARRELROLL - joueur->coolDownBarrelRoll) / (float)CD_BARRELROLL) * 10;
        if (nbSymboleBarrelRollP1 > 10)
            nbSymboleBarrelRollP1 = 10;
    }

    for (int i = 0; i < (int)nbSymboleBarrelRollP1; i++)
        progressBarrelRoll[i + 1] = L'#';

    texte = L"P1 Barrel Roll: ";
    for (int i = 0; i < texte.size(); i++)   //on ajoute le score au buffer
        buffer[HEIGHT + 2][i + posCurseur] = texte[i];

    for (int i = 0; i < 12; i++)
        buffer[HEIGHT + 2][i + texte.size() + posCurseur] = progressBarrelRoll[i];

    if (nbJoueur > 1)
    {
        //rempli le buffer progressBarrelRoll avec des espaces
        for (int i = 0; i < 12; i++)
            progressBarrelRoll[i] = L' ';

        progressBarrelRoll[0] = L'[';
        progressBarrelRoll[11] = L']';
        posCurseur = 12 + texte.size() + 5 + 25;

        if (joueur2->coolDownBarrelRoll == 0)
            nbSymboleBarrelRollP2 = 10;
        else
        {
            nbSymboleBarrelRollP2 = ((float)(CD_BARRELROLL - joueur2->coolDownBarrelRoll) / (float)CD_BARRELROLL) * 10;
            if (nbSymboleBarrelRollP2 > 10)
                nbSymboleBarrelRollP2 = 10;
        }
        for (int i = 0; i < (int)nbSymboleBarrelRollP2; i++)
            progressBarrelRoll[i + 1] = L'#';
        texte = L"P2 Barrel Roll: ";
        for (int i = 0; i < texte.size(); i++)   //on ajoute le score au buffer
            buffer[HEIGHT + 2][i + posCurseur] = texte[i];
        for (int i = 0; i < 12; i++)
            buffer[HEIGHT + 2][i + texte.size() + posCurseur] = progressBarrelRoll[i];

    }

    // Afficher le score
    if (gameOver)
        texte = L"Game Over!  Score: " + to_wstring(score1);
    else
    {
        if (joueur->nbVies >= 0)
            texte = L"Score: " + to_wstring(score1) + L"  P1 Lives: " + to_wstring(joueur->nbVies);
        else
            texte = L"Score: " + to_wstring(score1) + L"  P1 Lives: 0";
    }
    if (nbJoueur > 1)
    {
        if (joueur2->nbVies >= 0)
            texte += L"         P2 Lives: " + to_wstring(joueur2->nbVies);
        else
            texte += L"         P2 Lives: 0";
    }


    for (size_t i = 0; i < texte.size(); i++)   //on ajoute le score du joueur 1 au buffer
        buffer[HEIGHT + 3][i] = texte[i];

    // on affiche chaque ligne du buffer
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int y = 0; y < HEIGHT + 4; y++)
    {
        COORD bufferCoord = { 0, static_cast<SHORT>(y) };
        DWORD charsWritten;

        WriteConsoleOutputCharacterW(hConsole, buffer[y], WIDTH + 2, bufferCoord, &charsWritten);       //on ecrit chaque ligne du buffer
    */
}


//enleve les entites mortes de la liste d'entites
void Interface::enleverEntites()
{
    for (int i = 0; i < listEntites.size(); i++)
    {
		if (!listEntites[i]->enVie && !listEntites[i]->isPlayer)	 //wtf is this if statement
        {
            GameScene->removeItem(listEntites[i]->image);       //on enleve l'image de l'entite de la scene
            delete listEntites[i]->image;

            listEntites.erase(listEntites.begin() + i);
            i--;
			
        }
        else if (!listEntites[i]->enVie && listEntites[i]->isPlayer)
        {
            GameScene->removeItem(listEntites[i]->image);       //on enleve l'image de l'entite de la scene
            delete listEntites[i]->image;

            listEntites.erase(listEntites.begin() + i);
            i--;
        }
    }
}

string location = "\Textures\Scenery";
//execution du jeu
void Interface::executionJeu(int version)

{
    if (firststart)
    {
      //Animation du Background qui bouge
        /*QMovie* background1 = new QMovie("Textures\\Scenery\\water.gif");
        QMovie* background2 = new QMovie("Textures\\Scenery\\water.gif");
        qDebug() << "Current working directory: " << QDir::currentPath();
        QLabel* labelBackground1 = new QLabel;
        QLabel* labelBackground2 = new QLabel;

        labelBackground1->setMovie(background1);
        labelBackground2->setMovie(background2);
        QTimer::singleShot(0, [&]() {
        background1->start();
        background2->start();
            });


        labelBackground1->setFixedSize(2560, 1440);
        labelBackground2->setFixedSize(2560, 1440);

        
        labelBackground1->move(-500, -1440);
        labelBackground2->move(-500, 0);
        QPropertyAnimation* animation1 = new QPropertyAnimation(labelBackground1, "geometry");
        animation1->setDuration(10000); 
        animation1->setStartValue(QRect(labelBackground1->x(), labelBackground1->y(), labelBackground1->width(), labelBackground1->height()));
        animation1->setEndValue(QRect(labelBackground1->x(), labelBackground1->y() + 1440, labelBackground1->width(), labelBackground1->height()));

        QPropertyAnimation* animation2 = new QPropertyAnimation(labelBackground2, "geometry");
        animation2->setDuration(10000); 
        animation2->setStartValue(QRect(labelBackground2->x(), labelBackground2->y(), labelBackground2->width(), labelBackground2->height()));
        animation2->setEndValue(QRect(labelBackground2->x(), labelBackground2->y() + 1440, labelBackground2->width(), labelBackground2->height()));


        animation1->setLoopCount(-1); 
        animation2->setLoopCount(-1); 

        QParallelAnimationGroup * group = new QParallelAnimationGroup;
        group->addAnimation(animation1);
        group->addAnimation(animation2);

        group->setLoopCount(-1);
        group->start();
        GameScene->addWidget(labelBackground1);
        GameScene->addWidget(labelBackground2);*/

        QPixmap pngImg("Textures\\Scenery\\space.png");
        QGraphicsPixmapItem* img = new QGraphicsPixmapItem(pngImg);
        GameScene->addItem(img);
        img->moveBy(-50, -50);
        img->setScale(0.75);
        img->show();

        //proxy->setpos(0, 0);
        qDebug() << "Current working directory: " << QDir::currentPath();
        //QPixmap pixmap("plane.png");
     /*  QPixmap pixmap("plane.png");
       player1 = new QGraphicsPixmapItem(pixmap);

       // Create a QGraphicsDropShadowEffect
       QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
       // Set the color of the shadow
       shadowEffect->setOffset(50, 30);       // Set the offset of the shadow (x, y)
           QColor shadowColor(0, 0, 255, 125); 

       // Apply the drop shadow effect to the image item
       player1->setGraphicsEffect(shadowEffect);
       player1->setScale(0.25);
       GameScene->addItem(player1);
       player1->show();*/
        hideCursor();
        music.stopMusic();
        music.playMusic("Space.wav", 74016, 56609);
        //music.playMusic("OceanWorld.wav", 0, 117000);
        if (version > 0)     //si on a choisi autre chose que le mode seul
        {
            listEntites.emplace_back(make_unique<Joueur>((WIDTH / 2) + 5, HEIGHT - 1));   //ajoute le joueur a la liste d'entites
            joueur2 = static_cast<Joueur*>(listEntites.back().get());
            joueur2->enVie = true;
            joueur->posX = (WIDTH / 2) - 5;
            nbJoueur = 2;
        }
        firststart = false;
    }
    if (!gameOver)
    {
        gererInput();

        while (pause == true)
        {
            gererInput();   //sert a revenir au jeu si on a fait pause
            Sleep(10);
        }
        progressionDifficulte();
        updateEntites();
        gererCollisions();
        enleverEntites();
        updateAffichage();
        //Sleep(20);

        if (nbJoueur == 1 && joueur->nbVies < 0)
            gameOver = true;
        else if (nbJoueur == 2 && joueur->nbVies < 0 && joueur2->nbVies < 0)
            gameOver = true;
    }
    if (gameOver)
    {
        restart();
    }
    //Sleep(1000);
    showCursor();
}


//Set la taille de la console
void setConsoleSize()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        cerr << "Error getting console handle" << endl;
        return;
    }
    //COORD bufferSize = { WIDTH, HEIGHT };
    //SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Set la taille de la console
    SMALL_RECT windowSize = { 0, 0, WIDTH + 3, HEIGHT + 3 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

//cache le curseur de la console
void Interface::hideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//affiche le curseur de la console
void Interface::showCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}