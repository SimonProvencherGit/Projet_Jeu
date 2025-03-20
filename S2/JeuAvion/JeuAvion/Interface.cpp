#include "Interface.h"
#include <qdir.h>
#include <QPropertyAnimation>
#include <qparallelanimationgroup.h>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsView>
#include <QThread>
#include <chrono>

// lien pour un sprite : https://opengameart.org/content/custom-missiles


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
            if (e == nullptr)
            {

            }

            if (pixmapItem == nullptr)
            {
                return;
            }
            if (e->Originalimage == nullptr)
            {
                return;
            }
            if (e->image == nullptr)
            {
                return;
            }
            try {
                QPixmap revertpix = e->Originalimage->pixmap();
                e->image->setPixmap(revertpix);
            }
            catch (...)
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
    boss3 = nullptr;
}


//gere les inputs du joueur
void Interface::gererInput()
{
    //----------------------------------------------   test manette   ----------------------------------------------
    if (pause == false)
    {

        switch (dataManette[0])     //premiere valeur du data de la manette est un chiffre de 1 a 9 du joystick
        {
        case 1:
            if (joueur->posX > 2)
                joueur->posX -= 2;      //on deplace le joueur de 2 vers la gauche
            else if (joueur->posX > 1)
                joueur->posX--;
            if (joueur->posY > HEIGHT / 10)      //le joueur a acces au 9/10 de l'ecran
                joueur->posY--;
            break;

        case 2:
            if (joueur->posY > HEIGHT / 10)      //le joueur a acces au 9/10 de l'ecran
                joueur->posY--;
            break;

        case 3:
            if (joueur->posY > HEIGHT / 10)      //le joueur a acces au 9/10 de l'ecran
                joueur->posY--;
            if (joueur->posX < WIDTH - 2)
                joueur->posX += 2;
            else if (joueur->posX < WIDTH - 1)
                joueur->posX++;
            break;

        case 4:
            if (joueur->posX > 2)
                joueur->posX -= 2;      //on deplace le joueur de 2 vers la gauche
            else if (joueur->posX > 1)
                joueur->posX--;
            break;
        case 5:
            //le joystick est au centre donc on ne fait rien
            break;

        case 6:
            if (joueur->posX < WIDTH - 2)
                joueur->posX += 2;
            else if (joueur->posX < WIDTH - 1)
                joueur->posX++;
            break;

        case 7:
            if (joueur->posY < HEIGHT)
                joueur->posY++;
            if (joueur->posX > 2)
                joueur->posX -= 2;      //on deplace le joueur de 2 vers la gauche
            else if (joueur->posX > 1)
                joueur->posX--;
            break;

        case 8:
            if (joueur->posY < HEIGHT)
                joueur->posY++;
            break;

        case 9:
            if (joueur->posY < HEIGHT)
                joueur->posY++;
            if (joueur->posX < WIDTH - 2)
                joueur->posX += 2;
            else if (joueur->posX < WIDTH - 1)
                joueur->posX++;
            break;


        }
        //pour les boutons de la manette a l'emplacement 2->haut 3->bas 4->gauche 5->droite 
        if (dataManette[3] == 1)
        {
            if (joueur->shootTimer == 0 && joueur->barrelRollTimer <= 0)    //on tire si on peut
            {
                //listEntites.emplace_back(make_unique<BasicBullet>(joueur->posX + joueur->largeur / 2, joueur->posY - 1, true));
                joueurTir(joueur);
                joueur->shootTimer = joueur->shootCooldown;   //on reset le cooldown de tir du joueur pour que update puisse le faire baisser a chaque frame pour pouvoir retirer
            }
        }

        if (dataManette[2] == 1)
        {
            gameOver = true;
            dataManette[5] = 0;
        }

        if (dataManette[1] == 1)
        {
            if (explosionTimer == 0)
            {
                cdExplosion = 500;      //set le cooldown de l'explosion
                enExplosion = true;
                explosionTimer = cdExplosion;
                explosionPosY = joueur->posY - 1;
                shakeScene(GameScene, view, 10, 10);
            }
        }

        //dataManette[4] est declare en bas de la fonction hors du if(!pause)

        if (dataManette[5] == 1)
        {
            if (joueur->barrelRoll == false && joueur->coolDownBarrelRoll <= 0)
                joueur->barrelRoll = true;
        }


        if (GetAsyncKeyState('A') < 0)   //on verifie si la fleche gauche ou D est pressee
        {
            if (joueur->posX > 0)
                joueur->posX -= 10;      //on deplace le joueur de 2 vers la gauche
            if (joueur->posX < 0)
                joueur->posX = 0;
        }
        if (GetAsyncKeyState('D') < 0)
        {
            if (joueur->posX < WIDTH - joueur->largeur)
                joueur->posX += 10;
            if (joueur->posX > WIDTH - joueur->largeur)
                joueur->posX = WIDTH - joueur->largeur;
        }

        if (GetAsyncKeyState('W') < 0)
        {
            if (joueur->posY > 0)      //le joueur a acces au 9/10 de l'ecran
                joueur->posY -= 10;
            if (joueur->posY < 0)
                joueur->posY = 0;
        }

        if (GetAsyncKeyState('S') < 0)
        {
            if (joueur->posY < HEIGHT - joueur->hauteur)
                joueur->posY += 10;
            if (joueur->posY > HEIGHT - joueur->hauteur)
                joueur->posY = HEIGHT;
        }
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
            if (GetAsyncKeyState('A') < 0)   //on verifie si la fleche gauche ou D est pressee
            {
                if (joueur2->posX > 2)
                    joueur2->posX -= 2;      //on deplace le joueur de 2 vers la gauche
                else if (joueur2->posX > 1)
                    joueur2->posX--;
            }
            if (GetAsyncKeyState('D') < 0) {
                if (joueur2->posX < WIDTH - 2)
                    joueur2->posX += 2;
                else if (joueur2->posX < WIDTH - 1)
                    joueur2->posX++;
            }

            if (GetAsyncKeyState('W') < 0)
                if (joueur2->posY > HEIGHT / 10)      //le joueur a acces au 9/10 de l'ecran
                    joueur2->posY--;

            if (GetAsyncKeyState('S') < 0)
                if (joueur2->posY < HEIGHT)
                    joueur2->posY++;
            if (GetAsyncKeyState(VK_SPACE) < 0)
            {
                if (joueur2->shootTimer == 0 && joueur2->barrelRollTimer <= 0)    //on tire si on peut
                {
                    //listEntites.emplace_back(make_unique<BasicBullet>(joueur->posX + joueur->largeur / 2, joueur->posY - 1, true));
                    joueurTir(joueur2);
                    joueur2->shootTimer = joueur2->shootCooldown;   //on reset le cooldown de tir du joueur pour que update puisse le faire baisser a chaque frame pour pouvoir retirer

                }
            }
            if (GetAsyncKeyState('E') < 0)
            {
                if (joueur2->barrelRoll == false && joueur2->coolDownBarrelRoll <= 0)
                    joueur2->barrelRoll = true;
            }
            if (GetAsyncKeyState('R') < 0)
            {
                if (explosionTimer == 0)
                {

                    cdExplosion = 500;      //set le cooldown de l'explosion
                    enExplosion = true;
                    explosionTimer = cdExplosion;
                    explosionPosY = joueur2->posY - 1;
                    shakeScene(GameScene, view, 1000, 10);
                }
            }
        }


        if (explosionTimer > 0)
        {
            explosionTimer--;
            explosion();
        }
    }


    if (dataManette[4] == 1)
    {
        if (pause)
            pause = false;
        else if (!pause)
            pause = true;
        Sleep(200);
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
        listEntites.emplace_back(make_unique<angleBullet>(quelJoueur->posX + quelJoueur->largeur / 2 - 12, quelJoueur->posY - 1, 90 + 180, '|', true));
        break;
    case 3:
        for (int i = 80; i < 110; i += 10)
            listEntites.emplace_back(make_unique<angleBullet>(quelJoueur->posX + quelJoueur->largeur / 2 - 12, quelJoueur->posY - 1, i + 180, '|', true));
        break;
    case 5:
        for (int i = 70; i < 120; i += 10)
            listEntites.emplace_back(make_unique<angleBullet>(quelJoueur->posX + quelJoueur->largeur / 2 - 12, quelJoueur->posY - 1, i + 180, '|', true));
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
        explosionPosY -= 5;
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
            coterand = rand() % 2;
            if (coterand == 0)
                listEntites.emplace_back(make_unique<Tank>(WIDTH - 146, rand() % HEIGHT / 2));          //on fait spawn un ennemi a une position aleatoire en y, la position en x de WIDTH - 2 se fait changer dans le constructeur dependant du sens de l'ennemi
            else
                listEntites.emplace_back(make_unique<Tank>(1, rand() % HEIGHT / 2));
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
        case ORBITER:
            listEntites.emplace_back(make_unique<Orbiter>(posRand, 0));
            positionSpawnRandom();
            break;
        case EXPLODER:
            listEntites.emplace_back(make_unique<Exploder>(posRand, 0));
            positionSpawnRandom();
            break;
        case TURRET:
            listEntites.emplace_back(make_unique<Turret>(posRand, 0));
            positionSpawnRandom();
            break;
        case BOSS3_MAIN:
            listEntites.emplace_back(make_unique<Boss3>(WIDTH / 2 - 2, 0));     // -2 car le boss est 4 de long et on veut qu'il soit centre
            boss3 = static_cast<Boss3*>(listEntites.back().get());
            break;
        case BOSS3_SIDE:
            //if (nbSideBoss3 % 2 == 0)
            listEntites.emplace_back(make_unique<Boss3Side>(WIDTH / 2 - 20, 0));
            //else
                //listEntites.emplace_back(make_unique<Boss3Side>(WIDTH / 2 + 15, 0));  
            //nbSideBoss3++;
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
    static int nbPass = 0;
    static bool spawnPup = false;
    static bool allSideBossSpawned = false;

    enemySpawnTimer++;

    if (score1 < 600)
    {

        if (enemySpawnTimer >= 250 || cbVivant() < 6)          //on fait spawn une vague d'ennemis a toutes les 70 frames
            // if (enemySpawnTimer >= 100) //pour des tests
        {
            enemySpawn(1, BASIC);   //on fait spawn 3 ennemis a chaque vague
            enemySpawn(1, ARTILLEUR);
            //enemySpawn(1, ZAPER);
            //enemySpawn(1, AIMBOT);
            //enemySpawn(2, SIDEBOMBER);
            //enemySpawn(1, DIVEBOMBER);
            //enemySpawn(1, TANK);
            //enemySpawn(1, SHOTGUNNER);
           // enemySpawn(1, BOSS1_MAIN);

            if (spawnPowerUpStart)
            {
                spawnPowerUpStart = false;
                powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2 - 70);
                powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2);
            }
            enemySpawnTimer = 0;        //on reset le timer pour pouvoir spanw la prochaine vague d'ennemis
        }
    }
    else if (score1 >= 600 && score1 < 1300)
    {
        if (enemySpawnTimer >= 50)          //on fait spawn une vague d'ennemis a toutes les 60 frames
        {
            //enemySpawn(3, BASIC);   //on fait spawn 4 ennemis a chaque vague
            enemySpawn(5, DIVEBOMBER);
            enemySpawnTimer = 0;        //on reset le timer pour pouvoir spanw la prochaine vague d'ennemis
        }
    }
    else if (score1 >= 1300 && score1 < 2000)
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
    else if (score1 >= 2000 && !boss1Spawned)
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
    else if (score1 >= memScore && score1 <= memScore + 1000 && boss1Spawned && !boss2Spawned)   //on fait spawn des ennemis apres que le boss soit mort 
    {

        if (bossWaitTimer > 100)
        {
            if (enemySpawnTimer >= 150 || cbVivant() < 7)
            {
                enemySpawn(4, SIDEBOMBER);
                enemySpawn(1, AIMBOT);
                int nbZaper = 0;

                for (auto& e : listEntites)
                {
                    if (e->getTypeEnnemi() == TANK)
                        nbZaper++;
                }
                if (nbZaper < 2)
                    enemySpawn(1, ZAPER);
                enemySpawnTimer = 0;

            }
        }
        else
            bossWaitTimer++;
    }
    else if (score1 >= memScore + 1000 && score1 <= memScore + 1850 && boss1Spawned && !boss2Spawned)   //on fait spawn des ennemis apres que le boss soit mort 
    {
        if (enemySpawnTimer >= 5)
        {
            enemySpawn(1, DIVEBOMBER);
            enemySpawnTimer = 0;
            bossWaitTimer = 0;
        }
    }
    else if (score1 >= memScore + 1850 && score1 <= memScore + 2800 && boss1Spawned && !boss2Spawned)
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
    else if (score1 >= memScore + 2800 && !boss2Spawned)
    {
        if (cbVivant() == 0)
        {

            if (bossWaitTimer > 200)	 //on attend un certain temps apres la mort du dernier ennemi avant de spawn le boss
            {
                enemySpawn(1, BOSS2_MAIN);
                boss2Spawned = true;

                memScore = score1 + 300;     //on garde le score en memoire lorsque le boss apparait, on y ajoute 250 pour le score du boss afin de connaitre le score qd le boss meurt afin de faire apparaitre les prochains ennemis
                bossWaitTimer = 0;
            }
            else
                bossWaitTimer++;
        }
    }
    else if (score1 >= memScore && score1 < memScore + 850 && boss2Spawned)
    {
        if (enemySpawnTimer >= 100 || cbVivant() < 4)
        {
            enemySpawn(1, TURRET);
            enemySpawn(1, AIMBOT);
            nbPass++;
            if (nbPass % 2 == 0)
            {
                enemySpawn(1, EXPLODER);
                nbPass = 0;
            }
            enemySpawnTimer = 0;
        }
    }
    else if (score1 >= memScore + 850 && score1 < memScore + 1500 && boss2Spawned)
    {
        if (enemySpawnTimer >= 100 || cbVivant() < 4)
        {
            enemySpawn(1, ORBITER);
            enemySpawnTimer = 0;
            nbPass++;
            if (nbPass % 2 == 0)
            {
                enemySpawn(1, EXPLODER);
                nbPass = 0;
            }
        }

    }
    else if (score1 >= memScore + 1600 && score1 < memScore + 2400 && boss2Spawned && !boss3Spawned)
    {
        if (boss3)
            if (boss3->posX > 0 && boss3->posY > 0)
                for (auto& e : listEntites)
                    e->getPosBoss3(boss3->posX + boss3->largeur / 2 - 1, boss3->posY + boss3->hauteur / 2);            //donne la position du boss3 aux entites pour que les side boss puissent trourner autour

        if (spawnPowerUpStart)
        {
            spawnPowerUpStart = false;
            //powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2);
            //powerupSpawn(1, ADDBULLETS, WIDTH / 2 + 5, HEIGHT / 2);
            enemySpawn(1, BOSS3_MAIN);
        }
        if (boss3 != nullptr)
        {
            if (enemySpawnTimer >= 32 && !allSideBossSpawned)
            {
                nbPass++;
                if (nbPass <= 5)
                    enemySpawn(1, BOSS3_SIDE);
                else
                    allSideBossSpawned = true;              //ne pas oublier de le remettre a false dans la prochaine section de la progression pour qu'il respawn si on restart la game

                enemySpawnTimer = 0;
            }
        }
    }

}


//met a jour les entites a chaque frame
void Interface::updateEntites()
{
    double angle;       //pour les ennemis qui ont besoin de l'angle entre eux et le joueur
    static int sideBoss3WaitTimer = 0;
    static int boss3WaitTimer = 0;

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
                bufferBulletsUpdate.emplace_back(make_unique<BasicBullet>(e->posX + e->largeur / 2 + 12, e->posY + e->hauteur + 1, false));     //on cree un bullet a la position de l'ennemi qu'on met un buffer temporaire pour eviter de les ajouter a la liste d'entites pendant qu'on itere a travers d'elle  

            if (e->typeEntite == ENNEMI && e->ammoType == FRAGMENTING && e->moveTimer % e->shootCooldown == 0 && e->shoots)     //si c'est un ennemi qui tire des fragmenting bullets
                bufferBulletsUpdate.emplace_back(make_unique<FragmentingBullet>(e->posX + e->largeur / 2 + 12, e->posY + e->hauteur + 1, false));

            if ((e->typeEntite == ENNEMI || e->typeEntite == BOSS) && e->ammoType == LASER && e->moveTimer % e->shootCooldown == 0 && e->shoots)	//si c'est un ennemi qui tire des lasers
                bufferBulletsUpdate.emplace_back(make_unique<Laser>(e->posX + e->largeur / 2, e->posY + e->hauteur, false));

            if (e->getTypeEnnemi() == AIMBOT && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //si c'est un ennemi qui tire des missiles tete chercheuse
                bufferBulletsUpdate.emplace_back(make_unique<Homing>(e->posX + e->largeur / 2 + 12, e->posY + e->hauteur + 1, false));

            else if (e->getTypeEnnemi() == ORBITER && e->moveTimer % e->shootCooldown == 0 && e->shoots)
            {
                angle = atan2(joueur->posY - e->posY, joueur->posX - e->posX) * 180 / PI;     //retourne l'angle en degres entre l'entite et le joueur
                bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(e->posX + e->largeur / 2, e->posY - 1, angle, 'o', false));
            }
            else if (e->getTypeEnnemi() == EXPLODER && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //si c'est un ennemi qui tire des missiles tete chercheuse
            {
                cercleExplosion(5, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                e->enVie = false;
            }
            else if (e->getTypeEnnemi() == TURRET && e->moveTimer % e->shootCooldown == 0 && e->shoots)
            {
                angle = atan2(joueur->posY - e->posY, joueur->posX - e->posX) * 180 / PI;     //retourne l'angle en degres entre l'entite et le joueur

                for (int i = -10; i <= 10; i += 10)
                    bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(e->posX + e->largeur / 2, e->posY - 1, angle + i, 'o', false));
            }

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

            else if (e->getTypeEnnemi() == BOSS2_MAIN && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //si c'est le 2e boss
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

                if (e->nbVies >= 200)
                {
                    if (e->moveTimer % 90 == 0)
                    {
                        cercleTir(25, e->posX + e->largeur / 2 - 10, e->posY + e->hauteur / 2);
                        cercleTir(25, e->posX + e->largeur / 2 + 10, e->posY + e->hauteur / 2);
                    }
                    balayageTir(4, 2, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);

                }
                else if (e->nbVies < 200 && e->nbVies >= 90)
                {
                    balayageTir(4, 26, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                }
                else if (e->nbVies < 90)
                {
                    if (e->moveTimer % 100 == 0)
                    {
                        cercleTir(5, e->posX + e->largeur / 2 - 10, e->posY + e->hauteur / 2);
                        cercleTir(5, e->posX + e->largeur / 2 + 10, e->posY + e->hauteur / 2);
                    }
                    balayageTir(5, 1, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                }
                angleTirBoss += 5;
                if (angleTirBoss >= 360)
                    angleTirBoss = 0;
            }
            //----------- update du 3e boss -------------------
            else if (e->getTypeEnnemi() == BOSS3_MAIN)
            {
                if (boss3WaitTimer < 175)
                    boss3WaitTimer++;
                else
                {
                    if (e->moveTimer % 8 == 0)
                    {
                        if (e->nbVies < 200 && e->nbVies >= 90)
                        {
                            balayageTir(1, 5, e->posX + e->largeur / 2 + 4, e->posY + e->hauteur / 2);
                            balayageTir(1, 5, e->posX + e->largeur / 2 - 4, e->posY + e->hauteur / 2, 180);
                        }
                        else if (e->nbVies < 90)
                        {

                            balayageTir(5, 1, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                        }
                        angleTirBoss += 5;
                        if (angleTirBoss >= 360)
                            angleTirBoss = 0;
                    }
                }
            }
            else if (e->getTypeEnnemi() == BOSS3_SIDE)
            {
                if (sideBoss3WaitTimer < 175)
                    sideBoss3WaitTimer++;
                else
                {
                    if (e->moveTimer % e->shootCooldown == 0)
                    {
                        //randomTir(e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                        //balayageTir(1, 10, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                        angle = atan2(e->posY - boss3->posY, e->posX - boss3->posX) * 180 / PI;
                        bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(e->posX + e->largeur / 2, e->posY + e->hauteur, angle, 'o', false));

                        //cercleTir(10, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                    }
                }
            }
        }
    }
    for (auto& bullet : bufferBulletsUpdate)
    {
        if (bullet != nullptr)
            listEntites.push_back(move(bullet));	//on ajoute les bullets du buffer a la liste d'entites
    }
}

void Interface::cercleExplosion(int angle, int x, int y)
{
    for (int i = 0; i <= 360; i += angle)
        bufferBulletsUpdate.emplace_back(make_unique<TempBullet>(x, y, i, false));
}

void Interface::cercleTir(int angle, int x, int y)
{
    for (int i = 0; i <= 360; i += angle)
        bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(x, y, i, 'o', false));
}

void Interface::balayageTir(int nbBranches, int vitesseAngulaire, int x, int y, int angleStart)
{
    for (int i = 0; i < 360; i += 360 / nbBranches)
        bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(x, y, angleStart + angleTirBoss + i, 'o', false));

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
                                for (int i = 80; i < 110; i += 10)
                                    bufferBullets.emplace_back(make_unique<angleBullet>(e2->posX + e2->largeur / 2 - 12, e2->posY - 1, i, '|', false));

                            e2->perdVie(1);
                            damageeffect(e2->image, 100, e2.get());
                            if (e2->nbVies != 0)       //si l'ennemi n'a pas de vie comme
                                e->enVie = false;   //la bullet meurt si elle entre en collision avec un ennemi

                            if (!e2->enVie && (e2->typeEntite == ENNEMI || e2->typeEntite == BOSS))
                            {

                                score1 += customPoints(e2->getTypeEnnemi());

                                if (e2->getTypeEnnemi() == EXPLODER || e2->getTypeEnnemi() == BOSS3_SIDE)
                                    cercleExplosion(5, e2->posX + e2->largeur / 2, e2->posY + e2->hauteur / 2);

                                if (score1 % 500 <= 10 && score1 > 100 && score1 > scoreLastPup + 50)        //on fait spawn un powerup a chaque 500 points.  le scoreLastPup sert a ne pas faire spawn 2 pup back to back parfois
                                {
                                    powerupSpawn(1, ADDLIFE, e2->posX + e2->largeur / 2, e2->posY + e2->hauteur / 2);       //on fait spawn un powerup a la position de l'ennemi
                                    scoreLastPup = score1;
                                }
                                if (e2->typeEntite == BOSS && e2->getTypeEnnemi() != BOSS3_SIDE)
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
        break;
    case ORBITER:
        return 20;
        break;
    case EXPLODER:
        return 10;
        break;
    case TURRET:
        return 25;
        break;
    case BOSS3_MAIN:
        return 300;
        break;
    case BOSS3_SIDE:
        return 50;
        break;
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

//string location = "\Textures\Scenery";
//execution du jeu
void Interface::executionJeu(int version)
{
    //------------------section port serie---------------------
      // Ouvrir le port série
    HANDLE hSerial = CreateFile(L"COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);  // selectionne le port serie
    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << "Erreur d'ouverture du port série." << endl;
    }

    // Configurer les paramètres du port série
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cerr << "Impossible de lire l'état du port série." << endl;
        CloseHandle(hSerial);
    }
    dcbSerialParams.BaudRate = CBR_9600;  // set baud rate
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = MAXDWORD;  // Returns immediately if no data is available
    timeouts.ReadTotalTimeoutConstant = 0;    // No additional wait time
    timeouts.ReadTotalTimeoutMultiplier = 0;  // No per-byte delay
    SetCommTimeouts(hSerial, &timeouts);

    COMSTAT status;     //pour verifier si des donnees sont dispo dans le port serie avant de call la lecture du port serie
    DWORD errors;

    if (firststart)
    {
        //------------------------ section graphique ---------------------
        QPixmap pngImg("Textures\\Scenery\\water.png");
        QGraphicsPixmapItem* img = new QGraphicsPixmapItem(pngImg);
        GameScene->addItem(img);
        img->setScale(0.75);
        img->show();

        //proxy->setpos(0, 0);
        qDebug() << "Current working directory: " << QDir::currentPath();
        //QPixmap pixmap("plane.png");
        //hideCursor();
        music.stopMusic();
        music.playMusic("OceanWorld.wav", 0, 117000);

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
        ClearCommError(hSerial, &errors, &status);
        if (status.cbInQue > 0)   // Lire seulement si des données sont dispo
            readSerial(hSerial);
        gererInput();

        while (pause == true)
        {
            ClearCommError(hSerial, &errors, &status);
            if (status.cbInQue > 0)   // Lire seulement si des données sont dispo
                readSerial(hSerial);

            gererInput();   //sert a revenir au jeu si on a fait pause
            Sleep(10);
        }
        progressionDifficulte();
        updateEntites();
        gererCollisions();
        enleverEntites();
        //updateAffichage();
        //Sleep(20);

        if (nbJoueur == 1 && joueur->nbVies < 0)
            gameOver = true;
        else if (nbJoueur == 2 && joueur->nbVies < 0 && joueur2->nbVies < 0)
            gameOver = true;
    }
    if (gameOver)
    {
        restart();
        CloseHandle(hSerial);  // Fermer le port série
    }
    //Sleep(1000);
    //showCursor();
}


void Interface::readSerial(HANDLE hSerial)
{
    char buffer[56];  // Taille du buffer attendue
    DWORD bytesRead;
    static string response;  // Garde les données incomplètes d'une lecture à l'autre

    // Lire les données du port série si disponibles
    //DWORD errors;
    //COMSTAT status;
    //ClearCommError(hSerial, &errors, &status);

    //if (status.cbInQue > 0) { // s'il y a des données à lire
    if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';  // Terminer la chaîne
        response += buffer;  // Ajouter au buffer accumulé

        // Vérifier si on a une ligne complète (avec \r\n a la fin)
        size_t pos;
        while ((pos = response.find("\r\n")) != string::npos)
        {
            string line = response.substr(0, pos);  // Extraire la ligne complète
            response.erase(0, pos + 2);  // Supprimer la ligne traitée

            try {
                // Parser le JSON
                json jsonData = json::parse(line);
                //cout << "JSON reçu : " << jsonData.dump(4) << endl;

                // Mettre à jour les données de la manette
                dataManette[0] = jsonData["Joy"];
                dataManette[1] = jsonData["acc"];
                dataManette[2] = jsonData["but1"];      //en haut
                dataManette[3] = jsonData["but2"];      //en bas
                dataManette[4] = jsonData["but3"];      //gauche
                dataManette[5] = jsonData["but4"];      //droite
            }
            catch (json::parse_error& e) {
                //cerr << "Erreur JSON : " << e.what() << endl;
            }
        }
    }
    //}

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