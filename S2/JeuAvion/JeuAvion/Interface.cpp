#include "Interface.h"


// lien pour un sprite : https://opengameart.org/content/custom-missiles





void Interface::damageeffect(QGraphicsPixmapItem* pixmapItem, int durationMs, Entite* e) {
    auto start = std::chrono::high_resolution_clock::now();
    // si c'est joueur
    if (e->typeEntite == JOUEUR || e->getTypeEnnemi() == TURRET || e->getTypeEnnemi() == BOSS2_MAIN)
    {
        if (e->enVie == false)
        {
            return;
        }
        if (e->flashing == true)
        {
            return;
        }

        e->AnimatedSprite->spritesheet = e->DamageImage->pixmap();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        //qDebug() << "Execution time: " << duration << " ms";
        //Retourner l'image a l'originale
        QTimer::singleShot(500, [=]() mutable {

            if (e->enVie == true) {
                if (e == nullptr)
                {
                    return;
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
                    e->AnimatedSprite->spritesheet = e->Originalimage->pixmap();
                }
                catch (...)
                {
                    qDebug() << "Failed to revert image";
                }
                e->flashing = false;
            }
            });

    }
    // si ce n'est pas un joueur
    else if (e->typeEntite != JOUEUR) {
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
                    return;
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
                }
                e->flashing = false;
            }
            });
    }
}

Interface::Interface()
{
    //initialisation des 
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
    unitVie2 = nullptr;
    dixVie2 = nullptr;

    //rolling2 = nullptr;

    /*rolling = new Sprite("barrel_roll.png", "barrel_roll.json");
    rolling->setpos(joueur->posX, joueur->posY);
    rolling->start(70);
    rolling->setframe(1);

    rolling->pixmapItem->setScale(0.26);
    rolling->pixmapItem->setZValue(100);
    rolling->pixmapItem->show();
    GameScene->addItem(rolling->pixmapItem);
    */

    joueur->AnimatedSprite->setpos(joueur->posX, joueur->posY);
    joueur->Proppeller1->setpos(joueur->posX, joueur->posY);
    //joueur->AnimatedSprite->start(70);
    joueur->AnimatedSprite->setframe(6);

    loadBarrelRoll = new Sprite("loadingBarrelRoll.png", "loadingBarrelRoll.json");
    loadBarrelRoll->setpos(1725, 980);
    //loadBarrelRoll->start(170);
    loadBarrelRoll->setframe(59);
    loadBarrelRoll->pixmapItem->setScale(0.8);
    loadBarrelRoll->pixmapItem->setZValue(100);
    loadBarrelRoll->pixmapItem->show();
    GameScene->addItem(loadBarrelRoll->pixmapItem);
    updateBarrelRollCounter();

    loadExplosion = new Sprite("loadingExplosion.png", "loadingExplosion.json");
    loadExplosion->setpos(-5, 980);
    //loadExplosion->start(170);
    loadExplosion->setframe(59);
    loadExplosion->pixmapItem->setScale(0.8);
    loadExplosion->pixmapItem->setZValue(100);
    loadExplosion->pixmapItem->show();
    GameScene->addItem(loadExplosion->pixmapItem);
    updateExplosionCounter();

    unites = new QGraphicsPixmapItem(*ListImages[24]);
    GameScene->addItem(unites);
    unites->setScale(0.55);
    unites->show();
    unites->setPos(1890, 10);
    unites->setZValue(100);
    dizaines = new QGraphicsPixmapItem(*ListImages[24]);
    GameScene->addItem(dizaines);
    dizaines->setScale(0.55);
    dizaines->show();
    dizaines->setPos(1860, 10);
    dizaines->setZValue(100);
    centaines = new QGraphicsPixmapItem(*ListImages[24]);
    GameScene->addItem(centaines);
    centaines->show();
    centaines->setPos(1830, 10);
    centaines->setZValue(100);
    centaines->setScale(0.55);
    milliers = new QGraphicsPixmapItem(*ListImages[24]);
    GameScene->addItem(milliers);
    milliers->setScale(0.55);
    milliers->show();
    milliers->setPos(1800, 10);
    milliers->setZValue(100);

    coeur = new QGraphicsPixmapItem(*ListImages[23]);
    coeur->setPos(10, 10);
    coeur->setScale(0.12);
    coeur->setZValue(50);
    coeur->show();
    GameScene->addItem(coeur);

    QGraphicsPixmapItem* x = new QGraphicsPixmapItem(*ListImages[68]);
    x->setPos(70, 28);
    x->setScale(0.35);
    x->setZValue(50);
    x->show();
    GameScene->addItem(x);

    dixVie = new QGraphicsPixmapItem(*ListImages[58]);
    dixVie->setPos(105, 20);
    dixVie->setScale(0.45);
    dixVie->setZValue(50);
    dixVie->show();
    GameScene->addItem(dixVie);
    unitVie = new QGraphicsPixmapItem(*ListImages[58]);
    unitVie->setPos(130, 20);
    unitVie->setScale(0.45);
    unitVie->setZValue(50);
    unitVie->show();
    GameScene->addItem(unitVie);
}

void Interface::gererInput()
{
    //----------------------------------------------   partie manette   ----------------------------------------------
    if (pause == false)
    {
        //Fix rapide pour les coins l'animation quand l'avion est au coins
        if (joueur != nullptr)
        {
            if (joueur->doingbarrelroll == false)
            {
                if (joueur->posX == 0 || joueur->posX == 1851)
                {

                    joueur->AnimatedSprite->setframe(5);
                }
            }
        }
        if (joueur2 != nullptr)
        {
            if (joueur2->doingbarrelroll == false)
            {
                if (joueur2->posX == 0 || joueur2->posX == 1851)
                    joueur2->AnimatedSprite->setframe(5);
            }
        }
        if (joueur != nullptr)
        {
            switch (dataManette[0])     //premiere valeur du data de la manette est un chiffre de 1 a 9 du joystick
            {
            case 1:
                if (joueur->posX > 0)
                {
                    if (!joueur->doingbarrelroll)
                    {
                        tiltplayerright(joueur); // tilt le joueur a gauche
                        tiltresetimerjoueur1.stop();
                    }
                    joueur->posX -= 10;

                }
                if (joueur->posX < 0)
                    joueur->posX = 0;

                if (joueur->posY > 0)
                    joueur->posY -= 10;
                if (joueur->posY < 0)
                    joueur->posY = 0;
                break;

            case 2:
                if (joueur->posY > 0)
                    joueur->posY -= 10;
                if (!joueur->doingbarrelroll)
                    tiltresetimerjoueur1.start(10);
                break;

            case 3:
                if (joueur->posY > 0)
                    joueur->posY -= 10;
                if (joueur->posX < WIDTH - joueur->largeur)
                {
                    if (!joueur->doingbarrelroll)
                    {
                        tiltplayerleft(joueur); // tilt le joueur a gauche
                    }
                    joueur->posX += 10;
                    tiltresetimerjoueur1.stop();
                }
                if (joueur->posX > WIDTH - joueur->largeur)
                    joueur->posX = WIDTH - joueur->largeur;
                //else if (joueur->posX < WIDTH - 1)
                    //joueur->posX+=10;
                break;

            case 4:
                if (joueur->posX > 0)
                {
                    if (!joueur->doingbarrelroll)
                    {
                        tiltplayerright(joueur); // tilt le joueur a gauche
                        tiltresetimerjoueur1.stop();
                    }
                    joueur->posX -= 10;
                }                  
                if (joueur->posX < 0)
                    joueur->posX = 0;               
                break;
            case 5:
                if (!joueur->doingbarrelroll)
                    tiltresetimerjoueur1.start(10);
                break;

            case 6:
                if (joueur->posX < WIDTH - joueur->largeur)
                {
                    if (!joueur->doingbarrelroll)
                    {
                        tiltplayerleft(joueur); // tilt le joueur a gauche
                    }
                    joueur->posX += 10;
                    tiltresetimerjoueur1.stop();
                }
                if (joueur->posX > WIDTH - joueur->largeur)
                    joueur->posX = WIDTH - joueur->largeur;
                break;

            case 7:
                if (joueur->posY < HEIGHT - 45)
                    joueur->posY += 10;
                
                if (joueur->posX > 0)
                {
                    if (!joueur->doingbarrelroll)
                    {
                        tiltplayerright(joueur); // tilt le joueur a gauche
                        tiltresetimerjoueur1.stop();
                    }
                    joueur->posX -= 10;
                }
                if (joueur->posX < 0)
                    joueur->posX = 0;
                break;

            case 8:
                if (joueur->posY < HEIGHT - 45)
                    joueur->posY += 10;
                if (!joueur->doingbarrelroll)
                    tiltresetimerjoueur1.start(10);
                break;

            case 9:
                if (joueur->posY < HEIGHT - 45)
                    joueur->posY += 10;

                if (joueur->posX < WIDTH - joueur->largeur)
                {
                    if (!joueur->doingbarrelroll)
                    {
                        tiltplayerleft(joueur); // tilt le joueur a gauche
                    }
                    joueur->posX += 10;
                    tiltresetimerjoueur1.stop();
                }
                if (joueur->posX > WIDTH - joueur->largeur)
                    joueur->posX = WIDTH - joueur->largeur;
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
                    cdExplosion = 900;      //set le cooldown de l'explosion
                    enExplosion = true;
                    explosionTimer = cdExplosion;
                    explosionPosY = joueur->posY - 1;
                    manageexplosion.chainexplosion(joueur->posY);
                }
            }
            if (dataManette[6] == 1)            //muons ici 
            {
                if (explosionTimer > 100)             //chaque muons charge 1/9 du cooldown de l'explosion
                    explosionTimer -= 100;
                else
                    explosionTimer = 0;
            }

            //dataManette[4] est declare en bas de la fonction hors du if(!pause)

            if (dataManette[5] == 1)
            {
                if (joueur->barrelRoll == false && joueur->coolDownBarrelRoll <= 0)
                {
                    joueur->barrelRoll = true;
                    joueur->doingbarrelroll = true;
                    tiltresetimerjoueur1.stop();
                    //add function for barrelroll
                    joueur->tiltcounter = 0;
                    //joueur->AnimatedSprite->setframe(6);

                    if (dataManette[0] == 3 || dataManette[0] == 6 || oldDataManette[0] == 9)
                        joueur->AnimatedSprite->startreverse(50);
                    else 
                        joueur->AnimatedSprite->start(50);

                    joueur->Proppeller1->pixmapItem->hide();// turn off propeller

                    QTimer::singleShot(800, [=]() {
                        joueur->Proppeller1->pixmapItem->show();
                    });

                    QTimer::singleShot(800, [=]() {
                        joueur->AnimatedSprite->stop();
                        joueur->AnimatedSprite->setframe(5);
                        joueur->doingbarrelroll = false;
                    });
                }
            }
			//--------------------------------   partie clavier   ----------------------------------------------
            if(!utiliseManette)
            {
                if (GetAsyncKeyState('A') < 0)   //on verifie si la fleche gauche ou D est pressee
                {
                    if (joueur->posX > 0)
                    {
                        if (!joueur->doingbarrelroll)
                        {
                            tiltplayerright(joueur); // tilt le joueur a gauche
                        }
                        joueur->posX -= 10;
                        tiltresetimerjoueur1.stop();
                    }
                    if (joueur->posX < 0)
                        joueur->posX = 0;
                }
                else if (GetAsyncKeyState('D') == 0 && !joueur->doingbarrelroll)
                {
                    tiltresetimerjoueur1.start(10);

                }

                if (GetAsyncKeyState('D') < 0)
                {
                    if (joueur->posX < WIDTH - joueur->largeur)
                    {
                        if (!joueur->doingbarrelroll)
                        {
                            tiltplayerleft(joueur); // tilt le joueur a gauche
                        }
                        joueur->posX += 10;
                        tiltresetimerjoueur1.stop();
                    }
                    if (joueur->posX > WIDTH - joueur->largeur)
                        joueur->posX = WIDTH - joueur->largeur;
                }
                else if (GetAsyncKeyState('A') == 0 && !joueur->doingbarrelroll)
                {
                    tiltresetimerjoueur1.start(10);

                }

                if (GetAsyncKeyState('W') < 0)
                {
                    if (joueur->posY > 0)
                        joueur->posY -= 10;
                    if (joueur->posY < 0)
                        joueur->posY = 0;
                }

                if (GetAsyncKeyState('S') < 0)
                {
                    if (joueur->posY < HEIGHT - joueur->hauteur + 25)
                        joueur->posY += 10;
                    if (joueur->posY > HEIGHT - joueur->hauteur + 25)
                        joueur->posY = HEIGHT - joueur->hauteur + 25;
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
                    {

                        joueur->barrelRoll = true;
                        joueur->doingbarrelroll = true;
                        tiltresetimerjoueur1.stop();
                        //add function for barrelroll
                        joueur->tiltcounter = 0;
                        //joueur->AnimatedSprite->setframe(6);
                        if (GetAsyncKeyState('D') < 0 && GetAsyncKeyState('A') == 0)
                        {
                            joueur->AnimatedSprite->startreverse(50);
                        }
                        if (GetAsyncKeyState('A') < 0 && GetAsyncKeyState('D') == 0)
                        {
                            joueur->AnimatedSprite->start(50);
                        }
                        if (GetAsyncKeyState('A') == 0 && GetAsyncKeyState('D') == 0)
                        {
                            joueur->AnimatedSprite->start(50);
                        }
                        joueur->Proppeller1->pixmapItem->hide();// turn off propeller

                        QTimer::singleShot(800, [=]() {
                            joueur->Proppeller1->pixmapItem->show();
                        });

                        QTimer::singleShot(800, [=]() {
                            joueur->AnimatedSprite->stop();
                            joueur->AnimatedSprite->setframe(5);
                            joueur->doingbarrelroll = false;
                        });
                    }
                }
                if (GetAsyncKeyState('Q') < 0)
                {
                    if (explosionTimer == 0)
                    {

                        cdExplosion = 900;      //set le cooldown de l'explosion
                        enExplosion = true;
                        explosionTimer = cdExplosion;
                        explosionPosY = joueur->posY - 1;
                        manageexplosion.chainexplosion(joueur->posY);
                    }
                }

                if (GetAsyncKeyState('R') < 0)
                {
                    if (explosionTimer == 0)
                    {

                        cdExplosion = 900;      //set le cooldown de l'explosion
                        enExplosion = true;
                        explosionTimer = cdExplosion;
                        explosionPosY = joueur->posY - 1;
                        manageexplosion.chainexplosion(joueur->posY);
                    }
                }
            }
        }
        //******************************************* controle 2e joueur *******************************************
        if(!utiliseManette)
        {
            if (nbJoueur > 1 && joueur2 != nullptr)
            {
                if (GetAsyncKeyState('J') < 0)   //on verifie si la fleche gauche ou D est pressee
                {
                    if (joueur2->posX > 0)
                    {
                        if (!joueur2->doingbarrelroll)
                        {
                            tiltplayerright(joueur2); // tilt le joueur a gauche
                        }
                        joueur2->posX -= 10;//on deplace le joueur de 2 vers la gauche
                        tiltresetimerjoueur2.stop();
                    }
                    if (joueur2->posX < 0)
                        joueur2->posX = 0;
                }
                else if (GetAsyncKeyState('L') == 0 && !joueur2->doingbarrelroll)
                {
                    tiltresetimerjoueur2.start(10);

                }

                if (GetAsyncKeyState('L') < 0)
                {
                    if (joueur2->posX < WIDTH - joueur2->largeur)
                    {
                        if (!joueur2->doingbarrelroll)
                        {
                            tiltplayerleft(joueur2); // tilt le joueur a gauche
                        }
                        joueur2->posX += 10;
                        tiltresetimerjoueur2.stop();
                    }
                    if (joueur2->posX > WIDTH - joueur2->largeur)
                        joueur2->posX = WIDTH - joueur2->largeur;
                }
                else if (GetAsyncKeyState('J') == 0 && !joueur2->doingbarrelroll)
                {
                    tiltresetimerjoueur2.start(10);

                }

                if (GetAsyncKeyState('I') < 0)
                {
                    if (joueur2->posY > 0)      //le joueur a acces au 9/10 de l'ecran
                        joueur2->posY -= 10;
                    if (joueur2->posY < 0)
                        joueur2->posY = 0;
                }
                if (GetAsyncKeyState('K') < 0)
                {
                    if (joueur2->posY < HEIGHT - joueur2->hauteur + 25)
                        joueur2->posY += 10;
                    if (joueur2->posY > HEIGHT - joueur2->hauteur + 25)
                        joueur2->posY = HEIGHT - joueur2->hauteur + 25;
                }

                if (GetAsyncKeyState(VK_RSHIFT) < 0)
                {
                    if (joueur2->shootTimer == 0 && joueur2->barrelRollTimer <= 0)    //on tire si on peut
                    {
                        //listEntites.emplace_back(make_unique<BasicBullet>(joueur->posX + joueur->largeur / 2, joueur->posY - 1, true));
                        joueurTir(joueur2);
                        joueur2->shootTimer = joueur2->shootCooldown;   //on reset le cooldown de tir du joueur pour que update puisse le faire baisser a chaque frame pour pouvoir retirer

                    }
                }
                if (GetAsyncKeyState('O') < 0)
                {
                    if (joueur2->barrelRoll == false && joueur2->coolDownBarrelRoll <= 0)
                    {
                        joueur2->barrelRoll = true;
                        joueur2->doingbarrelroll = true;
                        tiltresetimerjoueur2.stop();
                        //add function for barrelroll
                        joueur2->tiltcounter = 0;
                        //joueur->AnimatedSprite->setframe(6);
                        if (GetAsyncKeyState('L') < 0 && GetAsyncKeyState('J') == 0)
                        {
                            joueur2->AnimatedSprite->startreverse(50);
                        }
                        if (GetAsyncKeyState('J') < 0 && GetAsyncKeyState('L') == 0)
                        {
                            joueur2->AnimatedSprite->start(50);
                        }
                        if (GetAsyncKeyState('J') == 0 && GetAsyncKeyState('L') == 0)
                        {
                            joueur2->AnimatedSprite->start(50);
                        }

                        // QTimer::singleShot(800, [=]() {
                          //   joueur2->Proppeller1->pixmapItem->show();
                          //   });

                        QTimer::singleShot(800, [=]() {
                            joueur2->AnimatedSprite->stop();
                            joueur2->AnimatedSprite->setframe(5);
                            joueur2->doingbarrelroll = false;
                        });
                    }

                }
                if (GetAsyncKeyState('U') < 0)
                {
                    if (explosionTimer == 0)
                    {

                        cdExplosion = 900;      //set le cooldown de l'explosion
                        enExplosion = true;
                        explosionTimer = cdExplosion;
                        explosionPosY = joueur2->posY - 1;
                        //shakeScene(GameScene, view, 1000, 10);
                        manageexplosion.chainexplosion(joueur2->posY);
                    }
                }


                //rolling2->setpos(joueur2->posX - 20, joueur2->posY - 25);

                /*if (!joueur2->invincible && joueur2->barrelRollTimer <= 0)
                {
                    //
                    // rolling->stop();
                    rolling2->setframe(1);
                }*/

                if (joueur2->posX == 0 || joueur2->posX == 1851)
                {
                    joueur2->AnimatedSprite->setframe(5);
                }

            }
        }
        else
        {
            if (nbJoueur > 1 && joueur2 != nullptr)
            {
                if (GetAsyncKeyState('A') < 0)   //on verifie si la fleche gauche ou D est pressee
                {
                    if (joueur2->posX > 0)
                    {
                        if (!joueur2->doingbarrelroll)
                        {
                            tiltplayerright(joueur2); // tilt le joueur a gauche
                        }
                        joueur2->posX -= 10;//on deplace le joueur de 2 vers la gauche
                        tiltresetimerjoueur2.stop();
                    }
                    if (joueur2->posX < 0)
                        joueur2->posX = 0;
                }
                else if (GetAsyncKeyState('D') == 0 && !joueur2->doingbarrelroll)
                {
                    tiltresetimerjoueur2.start(10);

                }

                if (GetAsyncKeyState('D') < 0)
                {
                    if (joueur2->posX < WIDTH - joueur2->largeur)
                    {
                        if (!joueur2->doingbarrelroll)
                        {
                            tiltplayerleft(joueur2); // tilt le joueur a gauche
                        }
                        joueur2->posX += 10;
                        tiltresetimerjoueur2.stop();
                    }
                    if (joueur2->posX > WIDTH - joueur2->largeur)
                        joueur2->posX = WIDTH - joueur2->largeur;
                }
                else if (GetAsyncKeyState('A') == 0 && !joueur2->doingbarrelroll)
                {
                    tiltresetimerjoueur2.start(10);

                }

                if (GetAsyncKeyState('W') < 0)
                {
                    if (joueur2->posY > 0)      //le joueur a acces au 9/10 de l'ecran
                        joueur2->posY -= 10;
                    if (joueur2->posY < 0)
                        joueur2->posY = 0;
                }
                if (GetAsyncKeyState('S') < 0)
                {
                    if (joueur2->posY < HEIGHT - joueur2->hauteur + 25)
                        joueur2->posY += 10;
                    if (joueur2->posY > HEIGHT - joueur2->hauteur + 25)
                        joueur2->posY = HEIGHT - joueur2->hauteur + 25;
                }

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
                    {
                        joueur2->barrelRoll = true;
                        joueur2->doingbarrelroll = true;
                        tiltresetimerjoueur2.stop();
                        //add function for barrelroll
                        joueur2->tiltcounter = 0;
                        //joueur->AnimatedSprite->setframe(6);
                        if (GetAsyncKeyState('L') < 0 && GetAsyncKeyState('J') == 0)
                        {
                            joueur2->AnimatedSprite->startreverse(50);
                        }
                        if (GetAsyncKeyState('J') < 0 && GetAsyncKeyState('L') == 0)
                        {
                            joueur2->AnimatedSprite->start(50);
                        }
                        if (GetAsyncKeyState('J') == 0 && GetAsyncKeyState('L') == 0)
                        {
                            joueur2->AnimatedSprite->start(50);
                        }

                        // QTimer::singleShot(800, [=]() {
                          //   joueur2->Proppeller1->pixmapItem->show();
                          //   });

                        QTimer::singleShot(800, [=]() {
                            joueur2->AnimatedSprite->stop();
                            joueur2->AnimatedSprite->setframe(5);
                            joueur2->doingbarrelroll = false;
                        });
                    }

                }
                if (GetAsyncKeyState('Q') < 0)
                {
                    if (explosionTimer == 0)
                    {

                        cdExplosion = 900;      //set le cooldown de l'explosion
                        enExplosion = true;
                        explosionTimer = cdExplosion;
                        explosionPosY = joueur2->posY - 1;
                        //shakeScene(GameScene, view, 1000, 10);
                        manageexplosion.chainexplosion(joueur2->posY);
                    }
                }

                if (joueur2->posX == 0 || joueur2->posX == 1851)
                {
                    joueur2->AnimatedSprite->setframe(5);
                }

            }
        }

        if (explosionTimer > 0)
        {
            explosionTimer--;       //if muons, met cette ligne en commentaire
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

    if (GetAsyncKeyState(VK_ESCAPE) < 0)
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
    switch (quelJoueur->nbBulletTir)
    {
    case 1:
        listEntites.emplace_back(make_unique<angleBullet>(quelJoueur->posX + quelJoueur->largeur / 2 - 25, quelJoueur->posY - 30, 90 + 180, '|', true));
        break;
    case 3:
        for (int i = 80; i < 110; i += 10)
            listEntites.emplace_back(make_unique<angleBullet>(quelJoueur->posX + quelJoueur->largeur / 2 - 25, quelJoueur->posY - 30, i + 180, '|', true));
        break;
    case 5:
        for (int i = 70; i < 120; i += 10)
            listEntites.emplace_back(make_unique<angleBullet>(quelJoueur->posX + quelJoueur->largeur / 2 - 25, quelJoueur->posY - 30, i + 180, '|', true));
        break;
    }
}


void Interface::explosion()
{

    if (enExplosion)
    {
        for (auto& e : listEntites)
        {
            if (e->enVie && e->posY >= explosionPosY && e->posY <= explosionPosY + 50 && !e->isPlayer && e->typeEntite != BOSS && e->typeEntite != POWERUP)	//on verifie si l'entite est dans une zone d'explosion qui avance vers le haut de l'ecran
            {
                if (e->ammoType == LASER && e->typeEntite == BULLET)    //regle un bug qui laisse les laser sur l'ecran qd tout explose
                {
                }
                else
                    e->enVie = false;
                //score += customPoints(e->getTypeEnnemi());
            }
        }
    }

    if (explosionPosY > 0)
        explosionPosY -= 8;
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
            listEntites.emplace_back(make_unique<Boss2>(WIDTH / 2-195, HEIGHT));
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
            listEntites.emplace_back(make_unique<Boss3Side>(WIDTH / 3, 0));
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
    static bool ONESHOT = false;
	static bool twoShot = false;
	static bool musicSpace = false;

    enemySpawnTimer++;

    if (score1 < 500)
    {

        if (enemySpawnTimer >= 250 || cbVivant() < 6)          //on fait spawn une vague d'ennemis a toutes les 70 frames
        {
            enemySpawn(1, BASIC);   
            enemySpawn(1, ARTILLEUR);
            //enemySpawn(1, ZAPER);
            //enemySpawn(1, AIMBOT);
            //enemySpawn(2, SIDEBOMBER);
            //enemySpawn(1, DIVEBOMBER);
            //enemySpawn(1, TANK);
            //enemySpawn(1, SHOTGUNNER);
            //enemySpawn(1, TURRET);
            //enemySpawn(1, ORBITER);
            //enemySpawn(1, EXPLODER);

            

           /*if (spawnPowerUpStart)
           {          
                //enemySpawn(1, EXPLODER);
                //enemySpawn(1, BOSS2_MAIN);
                //enemySpawn(1, BOSS1_MAIN);
                enemySpawn(1, BOSS3_MAIN);
                spawnPowerUpStart = false;
                //powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2 - 70);
                powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2);
           }*/
            

            enemySpawnTimer = 0;        //on reset le timer pour pouvoir spanw la prochaine vague d'ennemis
        }
    }
    else if (score1 >= 500 && score1 < 1400)
    {
        if (enemySpawnTimer >= 50)          //on fait spawn une vague d'ennemis a toutes les 60 frames
        {
            //enemySpawn(3, BASIC);   //on fait spawn 4 ennemis a chaque vague
            enemySpawn(5, DIVEBOMBER);
            enemySpawnTimer = 0;        //on reset le timer pour pouvoir spanw la prochaine vague d'ennemis
        }
    }
    else if (score1 >= 1400 && score1 < 2000)
    {
        if (enemySpawnTimer >= 200 || cbVivant() < 4)          //on fait spawn une vague d'ennemis a toutes les 50 frames
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

                Warning = new Sprite("warning.png", "warning.json");
                Warning->start(32);
                bossSpawnSound = true;
                enemySpawnTimer = 0;
                Warning->setpos(450, 400);
                Warning->pixmapItem->setScale(2.4);
                Warning->pixmapItem->setZValue(100);
                Warning->pixmapItem->show();
                GameScene->addItem(Warning->pixmapItem);

                bossSpawnSound = true;
                enemySpawnTimer = 0;
                //Sleep(5);
            }
            else if (!bossMusicStart && bossSpawnSound)
            {

                if (enemySpawnTimer >= 325)
                {
                    Warning->stop();
                    delete Warning;
                    sfxWarning.stopSFX();
                    music.playMusic("Boss1.wav", 0, 100000);
                    bossMusicStart = true;

                }
            }

            if (bossWaitTimer > 527)	 //on attend un certain temps apres la mort du dernier ennemi avant de spawn le boss
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
    else if (score1 >= memScore && score1 <= memScore + 800 && boss1Spawned && !boss2Spawned)   //on fait spawn des ennemis apres que le boss soit mort 
    {
        if (bossWaitTimer > 350)
        {
            if (!ONESHOT)
            {
                //music.playMusic("Forest.wav", 21639, 115195);
                BackManager->stopbackground();
                BackManager->setforest();
                BackManager->bougebackground();
                ONESHOT = true;
            }
        }
        if (bossWaitTimer > 370)
        {
            if (!twoShot)
            {
                music.playMusic("Forest.wav", 21639, 115195);
                twoShot = true;
            }
            if (enemySpawnTimer >= 175 || cbVivant() < 7)
            {
                enemySpawn(3, SIDEBOMBER);
                enemySpawn(1, AIMBOT);
                int nbZaper = 0;

                for (auto& e : listEntites)
                {
                    if (e->getTypeEnnemi() == ZAPER)
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
    else if (score1 >= memScore + 800 && score1 <= memScore + 1700 && boss1Spawned && !boss2Spawned)   //on fait spawn des ennemis apres que le boss soit mort 
    {
        if (enemySpawnTimer >= 6)
        {
            enemySpawn(1, DIVEBOMBER);
            enemySpawnTimer = 0;
            bossWaitTimer = 0;
        }
    }
    else if (score1 >= memScore + 1700 && score1 <= memScore + 2300 && boss1Spawned && !boss2Spawned)
    {
        if (enemySpawnTimer >= 280 || cbVivant() < 8)
        {
            enemySpawn(1, ARTILLEUR);
            enemySpawn(1, SIDEBOMBER);
            enemySpawn(1, TANK);
            enemySpawn(1, AIMBOT);
            enemySpawn(1, DIVEBOMBER);
            enemySpawn(1, BASIC);

            int nbZaper = 0;
            for (auto& e : listEntites)
            {
                if (e->getTypeEnnemi() == ZAPER)
                    nbZaper++;
            }
            if (nbZaper < 2)
                enemySpawn(1, ZAPER);
            enemySpawnTimer = 0;
        }
    }
    else if (score1 >= memScore + 2300 && !boss2Spawned)
    {
        if (cbVivant() == 0)
        {
            if (!bossMusicStart && !bossSpawnSound)
            {
                music.stopMusic();
                sfxWarning.playSFX("warning.wav");

                Warning = new Sprite("warning.png", "warning.json");
                Warning->start(32);
                bossSpawnSound = true;
                Warning->setpos(450, 400);
                Warning->pixmapItem->setScale(2.4);
                Warning->pixmapItem->setZValue(100);
                Warning->pixmapItem->show();
                GameScene->addItem(Warning->pixmapItem);

                bossSpawnSound = true;
                enemySpawnTimer = 0;
                //Sleep(5);
            }
            else if (!bossMusicStart && bossSpawnSound)
            {
                if (enemySpawnTimer >= 325)         //
                {
                    Warning->stop();
                    delete Warning;
                    sfxWarning.stopSFX();
                    music.playMusic("Boss2.wav", 12850, 73633);
                    bossMusicStart = true;
					
                }
            }

            if (bossWaitTimer > 527)	 //on attend un certain temps apres la mort du dernier ennemi avant de spawn le boss
            {
                enemySpawn(1, BOSS2_MAIN);
                boss2Spawned = true;
                ONESHOT = false;
                twoShot = false;

                memScore = score1 + 300;     //on garde le score en memoire lorsque le boss apparait, on y ajoute 250 pour le score du boss afin de connaitre le score qd le boss meurt afin de faire apparaitre les prochains ennemis
                bossWaitTimer = 0;
            }
            else
                bossWaitTimer++;
        }
    }
    else if (score1 >= memScore && score1 < memScore + 800 && boss2Spawned)
    {
        if (bossWaitTimer > 350)
        {
            if (!ONESHOT)
            {
                //music.playMusic("Forest.wav", 21639, 115195);
                BackManager->stopbackground();
                BackManager->setdesert();
                BackManager->bougebackground();
                ONESHOT = true;
            }
        }
        if (bossWaitTimer > 370)
        {
            if (!twoShot)
            {
                music.playMusic("Desert.wav", 21639, 115195);
                twoShot = true;
            }
            if (enemySpawnTimer >= 185 || cbVivant() < 4)
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
        else
            bossWaitTimer++;
    }
    else if (score1 >= memScore + 800 && score1 < memScore + 1500 && boss2Spawned)
    {
        if (enemySpawnTimer >= 200 || cbVivant() < 4)
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
        bossSpawnSound = false;
        bossMusicStart = false;
    }
    else if (score1 >= memScore + 1400 && boss2Spawned && !boss3Spawned)
    {
        if (cbVivant() == 0)
        {
            if (!bossMusicStart && !bossSpawnSound)
            {
                music.stopMusic();
                sfxWarning.playSFX("warning.wav");

                Warning = new Sprite("warning.png", "warning.json");
                Warning->start(32);
                bossSpawnSound = true;
                Warning->setpos(450, 400);
                Warning->pixmapItem->setScale(2.4);
                Warning->pixmapItem->setZValue(100);
                Warning->pixmapItem->show();
                GameScene->addItem(Warning->pixmapItem);

                bossSpawnSound = true;
                enemySpawnTimer = 0;
                //Sleep(5);
            }
            else if (!bossMusicStart && bossSpawnSound)
            {

                if (enemySpawnTimer >= 325)         //
                {
                    Warning->stop();
                    delete Warning;
                    sfxWarning.stopSFX();
                    music.playMusic("Boss3.wav", 592, 69148);
                    bossMusicStart = true;
                    enemySpawnTimer = 0;

                }
            }

        }
        if (bossMusicStart)
        {
            if (spawnPowerUpStart)
            {
                spawnPowerUpStart = false;
                //powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2);
                //powerupSpawn(1, ADDBULLETS, WIDTH / 2 + 5, HEIGHT / 2);
                enemySpawn(1, BOSS3_MAIN);
                nbPass = 0;
            }
            if (boss3 != nullptr)
            {
                if (enemySpawnTimer >= 42 && !allSideBossSpawned)
                {
                    if (spawnPowerUpStart)
                    {
                        spawnPowerUpStart = false;
                        //powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2);
                        //powerupSpawn(1, ADDBULLETS, WIDTH / 2 + 5, HEIGHT / 2);
                        enemySpawn(1, BOSS3_MAIN);
						ONESHOT = false;
						twoShot = false;
                    }

                    if (boss3 != nullptr)
                    {
                        if (enemySpawnTimer >= 42 && !allSideBossSpawned)
                        {
                            if (boss3->posX > 0 && boss3->posY > 0)
                                for (auto& e : listEntites)
                                    e->getPosBoss3(boss3->posX + boss3->largeur / 2 - 1, boss3->posY + boss3->hauteur / 2);
                            if (nbPass < 5)
                                enemySpawn(1, BOSS3_SIDE);
                            else
                            {
                                allSideBossSpawned = true;              //ne pas oublier de le remettre a false dans la prochaine section de la progression pour qu'il respawn si on restart la game
                                boss3Spawned = true;
                                memScore = score1 + 550;
                            }
                            enemySpawnTimer = 0;
                            nbPass++;
                        }
                    }
                    bossWaitTimer = 0;
                }
            }
        }
    }
    else if (score1 >= memScore && boss3Spawned)
    {
        
        if (enemySpawnTimer >= 185 || cbVivant() < 4)
        {
            /*if (!musicSpace)
            {
                music.stopMusic();
                music.playMusic("Space.wav", 21639, 115195);
                //BackManager->stopbackground();
                //BackManager->setspace();
                //BackManager->bougebackground();
                musicSpace = true;
            }*/

            enemySpawn(1, TURRET);
            enemySpawn(1, AIMBOT);
            enemySpawn(1, ORBITER);
            enemySpawn(2, DIVEBOMBER);
            enemySpawn(2, SIDEBOMBER);
            enemySpawn(1, ARTILLEUR);

            enemySpawnTimer = 0;
        }
    }
}

//met a jour les entites a chaque frame
void Interface::updateEntites()
{
    double angle;       //pour les ennemis qui ont besoin de l'angle entre eux et le joueur
    static int sideBoss3WaitTimer = 0;
    static int boss3WaitTimer = 0;
    int frame;
    static int memPosXBoss3 = 0;
	static int memPosYBoss3 = 0;
	static bool oneShot = true;
	static bool twoShot = true;
	static bool threeShot = true;
    static bool bossOneShot = true;
	static int bossMaxHp = 0;
    static int glitchTimer = 0;
	static int memVolume = 0;

    for (auto& e : listEntites)     //on parcourt la liste d'entites
    {
        if (e->enVie)
        {
            if (nbJoueur == 1)
                e->getPosJoueurs(joueur->posX, joueur->posY, joueur->enVie);   //on donne la position du joueur a chaque entite, va etre utliser pour les choses a tete chercheuse etc.

            else if (nbJoueur == 2)
            {
                if (joueur == nullptr && joueur2!=nullptr)       //si le joueur 1 est mort et le joueur 2 est en vie
                    e->getPosJoueurs(-1, -1, false, joueur2->posX, joueur2->posY, joueur2->enVie);
                else if (joueur2==nullptr && joueur!=nullptr)       //si le joueur 2 est mort et le joueur 1 est en vie
                    e->getPosJoueurs(joueur->posX, joueur->posY, joueur->enVie, -1, -1, false);
                else if (joueur!=nullptr && joueur2!=nullptr)       //si les 2 joueurs sont en vie
                    e->getPosJoueurs(joueur->posX, joueur->posX, joueur->enVie, joueur2->posX, joueur2->posY, joueur2->enVie);
            }

            e->update();    //on met a jour chaque entite

            if (joueur2 != nullptr)
                joueur2->Proppeller1->setpos(joueur2->posX + 11, joueur2->posY + 70);

            if (e->typeEntite == ENNEMI && e->ammoType == NORMAL && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //on verifie si c'est un ennemi et si sont compteur pour tirer est a 0
                bufferBulletsUpdate.emplace_back(make_unique<BasicBullet>(e->posX + e->largeur / 2 + 12, e->posY + e->hauteur + 1, false));     //on cree un bullet a la position de l'ennemi qu'on met un buffer temporaire pour eviter de les ajouter a la liste d'entites pendant qu'on itere a travers d'elle  

            if (e->typeEntite == ENNEMI && e->ammoType == FRAGMENTING && e->moveTimer % e->shootCooldown == 0 && e->shoots)     //si c'est un ennemi qui tire des fragmenting bullets
                bufferBulletsUpdate.emplace_back(make_unique<FragmentingBullet>(e->posX + e->largeur / 2 - 10, e->posY + e->hauteur + 1, false));

            if ((e->typeEntite == ENNEMI || e->typeEntite == BOSS) && e->ammoType == LASER && e->moveTimer % e->shootCooldown == 0 && e->shoots)	//si c'est un ennemi qui tire des lasers
                bufferBulletsUpdate.emplace_back(make_unique<Laser>(e->posX + e->largeur / 2 - 14, e->posY + e->hauteur - 14, false));

            if (e->getTypeEnnemi() == AIMBOT && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //si c'est un ennemi qui tire des missiles tete chercheuse
                bufferBulletsUpdate.emplace_back(make_unique<Homing>(e->posX + e->largeur / 2 + 12, e->posY + e->hauteur + 1, false));

            else if (e->getTypeEnnemi() == ORBITER && e->moveTimer % e->shootCooldown == 0 && e->shoots)
            {
                int joueurRand;
                
                if (joueur != nullptr && joueur2 != nullptr)
                {
                    joueurRand = rand() % 2;	//choisi un joueur en vie aleatoirement pour le suivre

                    if(joueurRand == 0)
						angle = atan2((joueur->posY + joueur->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur->posX + joueur->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;     //retourne l'angle en degres entre l'entite et le joueur
					else
						angle = atan2((joueur2->posY + joueur2->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur2->posX + joueur2->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;     //retourne l'angle en degres entre l'entite et le joueur
                }
                else if (joueur != nullptr && joueur2 == nullptr)
                    angle = atan2((joueur->posY + joueur->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur->posX + joueur->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;     //retourne l'angle en degres entre l'entite et le joueur

                else if (joueur == nullptr && joueur2 != nullptr)
                    angle = atan2((joueur2->posY + joueur2->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur2->posX + joueur2->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;     //retourne l'angle en degres entre l'entite et le joueur
                else
                    angle = atan2((joueur->posY + joueur->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur->posX + joueur->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;     //retourne l'angle en degres entre l'entite et le joueur

                bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(e->posX + e->largeur / 2, e->posY - 1, angle, 'o', false));
            }
            else if (e->getTypeEnnemi() == EXPLODER && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //si c'est un ennemi qui tire des missiles tete chercheuse
            {
                cercleTir(10, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                //cercleExplosion(5, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                e->enVie = false;
            }
            else if (e->getTypeEnnemi() == TURRET && e->moveTimer % e->shootCooldown == 0 && e->shoots)
            {     
                if (e->joueurRand == 0)
                    angle = atan2((joueur->posY + joueur->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur->posX + joueur->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;
                else if (e->joueurRand == 1)
                    angle = atan2((joueur2->posY + joueur2->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur2->posX + joueur2->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;
                else
                    angle = atan2((joueur->posY + joueur->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur->posX + joueur->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;
                //angle = atan2((joueur->posY + joueur->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur->posX + joueur->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;     //retourne l'angle en degres entre l'entite et le joueur
                if (angle < 0)
                    frame = angle * -1;
                else
                    frame = 360 - angle;

                for (int i = -10; i <= 10; i += 10)
                    bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(e->posX + e->largeur / 2, e->posY + e->hauteur / 2 - 1, angle + i, 'o', false));
            }
            if (e->getTypeEnnemi() == TURRET)
            {
				if (e->joueurRand == 0)
                    angle = atan2((joueur->posY + joueur->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur->posX + joueur->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;
                else if (e->joueurRand == 1)
					angle = atan2((joueur2->posY + joueur2->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur2->posX + joueur2->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;
				else
					angle = atan2((joueur->posY + joueur->hauteur / 2) - (e->posY + e->hauteur / 2), (joueur->posX + joueur->largeur / 2) - (e->posX + e->largeur / 2)) * 180 / PI;     //retourne l'angle en degres entre l'entite et le joueur
                
                angle = angle * -1 + 180;     //on inverse l'angle pour que le sprite regarde vers le joueur

                if (angle < 0)
                    frame = (angle * -1) / 22.5 - 1; //DONT TOUCH -1  or else everything implodes
                else
                    frame = (360 - angle - 10) / 22.5;     //retourne l'angle en degres entre l'entite et le joueur

                e->AnimatedSprite->setframe(frame);
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

            //----------- update du 2e boss -------------------
            else if (e->getTypeEnnemi() == BOSS2_MAIN && e->moveTimer % e->shootCooldown == 0 && e->shoots)    //si c'est le 2e boss
            {
                if (oneShot)
                {
					oneShot = false;
					bossMaxHp = e->nbVies;
                }

                if (e->nbVies % 70 == 0 && spawnAddLife)
                {
                    powerupSpawn(1, ADDLIFE, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                    spawnAddLife = false;
                }
                else if (e->nbVies % 70 != 0)
                    spawnAddLife = true;

                //if (e->moveTimer % 8 == 0)
                  //  randomCibleTir(e->posX + e->largeur / 2, e->posY + e->hauteur / 2);

                if (e->nbVies >= 2*bossMaxHp/3)
                {
                    if (e->moveTimer % 125 == 0)
                    {
                        //cercleTir(25, e->posX + e->largeur / 2 - 50, e->posY + e->hauteur / 2);
                        cercleTir(25, e->posX + e->largeur / 2, e->posY + e->hauteur / 2 - 20);
                    }
                    balayageTir(4, 2, e->posX + e->largeur / 2, e->posY + e->hauteur / 2 - 20);

                    if (e->moveTimer % 9 == 0)
                        randomCibleTir(e->posX + e->largeur / 2, e->posY + e->hauteur / 2 - 20);
                }
                else if (e->nbVies < 2 * bossMaxHp / 3 && e->nbVies >= bossMaxHp/3)
                {
                    balayageTir(4, 28, e->posX + e->largeur / 2, e->posY + e->hauteur / 2 - 20);
                    if (e->moveTimer % 120 == 0)
                        cercleTir(25, e->posX + e->largeur / 2, e->posY + e->hauteur / 2 - 20);
                    if (e->moveTimer % 18 == 0)
                        randomCibleTir(e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                }
                else if (e->nbVies < bossMaxHp/3)
                {
                    if (e->moveTimer % 200 == 0)
                    {
                        cercleTir(10, e->posX + e->largeur / 2, e->posY + e->hauteur / 2 - 20);
                        //cercleTir(5, e->posX + e->largeur / 2 + 50, e->posY + e->hauteur / 2);
                    }
                    balayageTir(5, 1, e->posX + e->largeur / 2, e->posY + e->hauteur / 2 - 20);

                    if (e->moveTimer % 8 == 0)
                        randomCibleTir(e->posX + e->largeur / 2, e->posY + e->hauteur / 2 - 20);
                }
                angleTirBoss += 5;
                if (angleTirBoss >= 360)
                    angleTirBoss = 0;
            }
            //----------- update du 3e boss -------------------
            else if (e->getTypeEnnemi() == BOSS3_MAIN )
            {
				if (bossOneShot)
				{
					bossMaxHp = e->nbVies;
					bossOneShot = false;
				}

                if (boss3->posX > 0 && boss3->posY > 0)
                    for (auto& e : listEntites)
                        e->getPosBoss3(boss3->posX + boss3->largeur / 2 - 1, boss3->posY + boss3->hauteur / 2);            //donne la position du boss3 aux entites pour que les side boss puissent trourner autour
                if (boss3WaitTimer < 175)
                    boss3WaitTimer++;
                else
                {
                    if (e->moveTimer % 18 == 0)
                    {
                        if (e->nbVies >= bossMaxHp/2)
                        {
                            balayageTir(1, 5, e->posX + e->largeur / 2 + 4, e->posY + e->hauteur / 2 - 35);
                            balayageTir(1, 5, e->posX + e->largeur / 2 - 4, e->posY + e->hauteur / 2 - 35, 180);
                        }
                        else if (e->nbVies < bossMaxHp / 2)
                        {
                            if (twoShot)
                            {
								twoShot = false;
								glitchEffect(true);
								music.stopMusic();
                                glitchSFX.playSFX("glitch.wav");
								memVolume = sfx.getvolume();
                                sfx.setVolume(0);
                                
								BackManager->stopbackground();
                                BackManager->setspace();
								BackManager->bougebackground();
                            }
                            else if (!twoShot)
                            {
                                if (glitchTimer < 5)
                                {
                                    if (nbJoueur > 1)
                                    {
										if (joueur != nullptr)
											joueur->invincible = true;
                                        if (joueur2 != nullptr)
                                            joueur2->invincible = true;
									}
                                    else
                                    {
                                        if (joueur != nullptr)
                                            joueur->invincible = true;
                                    }
                                        glitchTimer++;
                                    
								}
                                else if(glitchTimer >= 5 && threeShot)
                                {
									threeShot = false;
                                    glitchEffect(false);
									sfx.setVolume(memVolume);
									music.playMusic("Boss3.wav", 21639, 115195);

                                    if (nbJoueur > 1)
                                    {
                                        if (joueur != nullptr)
                                            joueur->invincible = false;
                                        if (joueur2 != nullptr)
                                            joueur2->invincible = false;
                                    }
                                    else
                                    {
                                        if (joueur != nullptr)
                                            joueur->invincible = false;
                                    }
                                }
                            }

                            balayageTir(5, 1, e->posX + e->largeur / 2, e->posY + e->hauteur / 2 - 35);
                        }
                        angleTirBoss += 3;
                        if (angleTirBoss >= 360)
                            angleTirBoss = 0;
                    }
                }
				memPosXBoss3 = boss3->posX + boss3->largeur / 2 ;
                memPosYBoss3 = boss3->posY + boss3->hauteur / 2;
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
                        angle = atan2(e->posY - memPosYBoss3, e->posX - memPosXBoss3) * 180 / PI;
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
    int joueurRand;
    int dx = 0;
	int dy = 0;

    if (nbJoueur > 1)
    {
		joueurRand = rand() % 2;	
		if (joueurRand == 0)
        {
            if(joueur != nullptr)
            {
                dx = joueur->posX - x;
                dy = joueur->posY - y;
			}
			else if (joueur2 != nullptr)
            {
                dx = joueur2->posX - x;
                dy = joueur2->posY - y;
            }
        }
        else
        {
            if (joueur2 != nullptr)
            {
                dx = joueur2->posX - x;
                dy = joueur2->posY - y;
            }
            else if(joueur!= nullptr)
            {
                dx = joueur->posX - x;
                dy = joueur->posY - y;
            }
        }
	}
    else
    {
        dx = joueur->posX - x;
        dy = joueur->posY - y;
    }
    
    //calcule l'angle entre le joueur et le boss et tire aleatoirement dans un cone de 40 degres vers le joueur
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
            if (joueur != nullptr)
            {
                if (e->typeEntite == POWERUP && e->enCollision(joueur->posX, joueur->posY, joueur->largeur, joueur->hauteur))
                {
                    switch (e->power_up)        //on verifie quel type de powerup c'est pour faire les actions appropriees
                    {
                    case ADDLIFE:
                        joueur->nbVies++;
                        updateHealthCounter();
                        break;

                    case ADDBULLETS:
                        joueur->nbBulletTir += 2;
                        joueur->shootCooldown += 8;
                        break;
                    }
                    e->enVie = false;
                }
                else if (e->enCollision(joueur->posX, joueur->posY, joueur->largeur, joueur->hauteur) && joueur->invincibleTimer <= 0 && joueur->barrelRollTimer <= 0 && !e->isPlayer)     //on verifie si un entite entre en collision avec le joueur et verifie que e n'est pas joueur
                {
                    if ((e->typeEntite == ENNEMI || e->typeEntite == BOSS) && e->collisionJoueur == false)
                    {
                        joueur->perdVie(2);	 //le joueur perd 2 vies si il entre en collision avec un ennemi
                        joueur->invincible = true;     //le joueur est invincible pour un court moment apres
                        damageeffect(joueur->image, 100, joueur);

                        updateHealthCounter();
                        e->collisionJoueur = true;
                    }
                    else if (e->typeEntite == BULLET && e->collisionJoueur == false && !e->bulletAllie)     //si le joueur entre en collision avec une bullet ennemi sans etre en barrel roll il perd une vie
                    {
                        joueur->perdVie(1);    //le joueur perd 1 vie si il entre en collision avec une bullet ennemi et s'il est pas invincible
                        joueur->invincible = true;     //le joueur est invincible pour un court moment apres
                        damageeffect(joueur->image, 100, joueur);
                        updateHealthCounter();

                        if (e->typeEntite == BULLET && e->ammoType == LASER)
                        {
                        }
                        else
                        {
                            e->enVie = false;   //la bullet meurt si elle entre en collision avec le joueur
                            e->collisionJoueur = true;
                        }
                    }
                }
            }
            //partie ou on gere les collision avec les bullets alliees
            if (e->typeEntite == BULLET && e->bulletAllie)  //on verifie si c'est un bullet allie tire par le joueur
            {
                for (auto& e2 : listEntites)	//on parcourt la liste d'entites pour voir si la bullet entre en collision avec un ennemi
                {
                    if (e2->enVie)
                    {
                        if (e2->enVie && e2->enCollision(e->posX, e->posY, e->largeur, e->hauteur) && e2->symbole != e->symbole && e2->typeEntite != POWERUP && !e2->isPlayer)       // si qqlch entre en collision avec la bullet allie et le e->symbole est pour pas que la bullet entre en collision avec elle meme 
                        {
                            if (e2->ammoType == FRAGMENTING && e2->typeEntite == BULLET && !e2->bulletAllie)      //si c'est un fragmenting bullet d'unennemi
                                for (int i = 80; i < 110; i += 10)
                                    bufferBullets.emplace_back(make_unique<angleBulletFrag>(e2->posX + e2->largeur / 2 - 12, e2->posY - 1, i, '|', false));


                            //if ((e2->typeEntite == BULLET && e2->ammoType == LASER || (e2->ammoType == ANGLE && e2->typeEntite == BOSS)) || e2->invincible)	   //si c'est pas un laser ou si l'ennemi est invincible on fait rien
                            if ((e2->typeEntite == BULLET && e2->ammoType == LASER) || e2->invincible || (e2->typeEntite == BULLET && e2->ammoType == ANGLE) || (e2->typeEntite == BULLET && e2->ammoType == TEMP))	   //g enlever le bout du milieu, a voir si ca cause des bug
                            {
                            }
                            else
                            {
                                e2->perdVie(1);
                                damageeffect(e2->image, 100, e2.get());
                                e->enVie = false;           //la bullet meurt si elle entre en collision avec un ennemi
                                
                            }


                            //if (e2->nbVies != 0)       //si l'ennemi n'a pas de vie comme
                                //e->enVie = false;   //la bullet meurt si elle entre en collision avec un ennemi

                            if (!e2->enVie && (e2->typeEntite == ENNEMI || e2->typeEntite == BOSS))	 //si l'ennemi est mort
                            {

                                score1 += customPoints(e2->getTypeEnnemi());

                                manageexplosion.enemydeathexplosion(e2->posX, e2->posY);             // explosion a la position de l'entite qui meurt

                                if (e2->getTypeEnnemi() == EXPLODER || e2->getTypeEnnemi() == BOSS3_SIDE)
                                {
                                    cercleTir(10, e2->posX + e2->largeur / 2, e2->posY + e2->hauteur / 2);
                                    manageexplosion.shakeScene(GameScene, view, 40, 10); // shake ecran quand explose
                                        
                                    //cercleExplosion(10, e2->posX + e2->largeur / 2, e2->posY + e2->hauteur / 2);
                                }
                                if (score1 % 500 <= 10 && score1 > 100 && score1 > scoreLastPup + 50)        //on fait spawn un powerup a chaque 500 points.  le scoreLastPup sert a ne pas faire spawn 2 pup back to back parfois
                                {
                                    powerupSpawn(1, ADDLIFE, e2->posX + e2->largeur / 2, e2->posY + e2->hauteur / 2);       //on fait spawn un powerup a la position de l'ennemi
                                    scoreLastPup = score1;
                                }
                                if (e2->typeEntite == BOSS && e2->getTypeEnnemi() != BOSS3_SIDE)
                                {
                                    if (e2->getTypeEnnemi() == BOSS1_MAIN)
                                    {
                                        music.stopMusic();
                                        manageexplosion.bossdeath();
									}
									else if (e2->getTypeEnnemi() == BOSS2_MAIN)
									{
										music.stopMusic();
										manageexplosion.bossdeath();
									}
                                    powerupSpawn(1, ADDLIFE, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                                }
                            }
                        }
                    }
                }
            }
            else
                e->collisionJoueur = false;

            
            if (nbJoueur > 1 && joueur2!= nullptr)
            {
                
                if (e->typeEntite == POWERUP && e->enCollision(joueur2->posX, joueur2->posY, joueur2->largeur, joueur2->hauteur))
                {
                    switch (e->power_up)        //on verifie quel type de powerup c'est pour faire les actions appropriees
                    {
                    case ADDLIFE:
                        joueur2->nbVies++;
                        updateHealthCounter();
                        break;

                    case ADDBULLETS:
                        joueur2->nbBulletTir += 2;
                        joueur2->shootCooldown += 8;
                        break;
                    }
                    e->enVie = false;
                }

                if (e->enCollision(joueur2->posX, joueur2->posY, joueur2->largeur, joueur2->hauteur) && joueur2->invincibleTimer <= 0 && joueur2->barrelRollTimer <= 0 && !e->isPlayer)     //on verifie si un entite entre en collision avec le joueur et verifie que e n'est pas joueur
                {
                    if ((e->typeEntite == ENNEMI || e->typeEntite == BOSS) && e->collisionJoueur == false)
                    {
                        joueur2->perdVie(2);	 //le joueur perd 2 vies si il entre en collision avec un ennemi
                        joueur2->invincible = true;     //le joueur est invincible pour un court moment apres
                        damageeffect(joueur2->image, 100, joueur2);

                        updateHealthCounter();
                        e->collisionJoueur = true;
                    }
                    else if (e->typeEntite == BULLET && e->collisionJoueur == false && !e->bulletAllie)     //si le joueur entre en collision avec une bullet ennemi sans etre en barrel roll il perd une vie
                    {
                        joueur2->perdVie(1);    //le joueur perd 1 vie si il entre en collision avec une bullet ennemi et s'il est pas invincible
                        joueur2->invincible = true;     //le joueur est invincible pour un court moment apres
                        damageeffect(joueur2->image, 100, joueur2);
                        updateHealthCounter();

                        if (e->typeEntite == BULLET && e->ammoType == LASER)
                        {
                        }
                        else
                        {
                            e->enVie = false;   //la bullet meurt si elle entre en collision avec le joueur
                            e->collisionJoueur = true;
                        }
                    }
                    
                }
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
        return 20;
        break;
    case TANK:
        return 40;
        break;
    case ARTILLEUR:
        return 30;
        break;
    case DIVEBOMBER:
        return 20;
        break;
    case ZAPER:
        return 40;
        break;
    case AIMBOT:
        return 40;
        break;
    case BOSS1_MAIN:
        powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 4);
        bossMusicStart = false;
        bossSpawnSound = false;
        return 100;
        break;
    case BOSS1_SIDE:
        return 50;
        break;
    case SIDEBOMBER:
        return 20;
        break;
    case BOSS2_MAIN:
        powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 4);
        return 300;
        break;
    case ORBITER:
        return 40;
        break;
    case EXPLODER:
        return 10;
        break;
    case TURRET:
        return 40;
        break;
    case BOSS3_MAIN:
        if (cbVivant() == 0)
        {
			music.stopMusic();
			music.playMusic("Space.wav", 21639, 115195);
        }
        return 300;
        break;
    case BOSS3_SIDE:
        if (cbVivant() == 0)
        {
            music.stopMusic();
            music.playMusic("Space.wav", 21639, 115195);
        }
        return 50;
        break;
    }
    return 0;
}

void Interface::restart()
{
    for (auto& e : listEntites)
    {
        if (e->ammoType == LASER && e->typeEntite == BULLET)    //regle un bug qui laisse les laser sur l'ecran qd tout explose
        {
        }
        else
            e->enVie = false;
    }
	for (int i = 0; i < 7; i++)
        dataManette[i] = 0;
	
    enleverEntites();
    gameOver = false;
    if (joueur != nullptr)
    {
        joueur2->enVie = false;
        enleverEntites();
    }
    listEntites.emplace_back(make_unique<Joueur>(WIDTH / 2 - (72.5), HEIGHT - 66.25));   //ajoute le joueur a la liste d'entites
    joueur = static_cast<Joueur*>(listEntites.back().get());
    joueur->posX = (WIDTH / 2) - 50;
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

    BackManager->stopbackground();
    BackManager->setocean();
    BackManager->bougebackground();

    updateHealthCounter();

	utiliseManette = false;

    music.stopMusic();
    Cooptimer.stop();
    Solotimer.stop();

    if (loadBarrelRoll2 != nullptr)
    {
        delete unitVie2;
        delete dixVie2;
        delete loadBarrelRoll2;
        loadBarrelRoll2 = nullptr;
        delete loadExplosion2;
        delete coeur2;
        delete x2;
    }
    delete BackManager;
    nbJoueur = 1;

    firststart = true;
    music.playMusic("MainMenu.wav", 65548, 63989);
    GererMenu* menu = new GererMenu();
    view->setScene(menu);
}

//enleve les entites mortes de la liste d'entites
void Interface::enleverEntites()
{

    for (int i = 0; i < listEntites.size(); i++)
    {
        if (!listEntites[i]->enVie && !listEntites[i]->isPlayer)
        {
            GameScene->removeItem(listEntites[i]->image);       //on enleve l'image de l'entite de la scene
            delete listEntites[i]->image;
            delete listEntites[i]->AnimatedSprite;

            listEntites.erase(listEntites.begin() + i);
            i--;

        }
        else if (!listEntites[i]->enVie && listEntites[i]->isPlayer)
        {
            if (joueur != nullptr)
            {
                if (!joueur->enVie)
                {
                    delete listEntites[i]->AnimatedSprite;
                    delete joueur->Proppeller1;
                    //GameScene->removeItem(rolling->pixmapItem);
                    joueur = nullptr;
                }
            }
            if (joueur2 != nullptr)
            {
                if (!joueur2->enVie && listEntites[i]->AnimatedSprite == joueur2->AnimatedSprite)
                {

                        delete listEntites[i]->AnimatedSprite;
                        //GameScene->removeItem(rolling2->pixmapItem);
                        delete joueur2->Proppeller1;
                        joueur2 = nullptr;
                    
                    
                }
            }
            //GameScene->removeItem(listEntites[i]->image);       //on enleve l'image de l'entite de la scene
            //delete listEntites[i]->image;
            
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
    //HANDLE hSerial = CreateFile(L"COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);  // selectionne le port serie
    COMSTAT status;     //pour verifier si des donnees sont dispo dans le port serie avant de call la lecture du port serie
    DWORD errors;

    if (firststart)
    {
        QObject::connect(&tiltresetimerjoueur1, &QTimer::timeout, [=]() {
            resettilt(joueur);
        });


        hSerial = CreateFile(L"COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);  // selectionne le port serie

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

        PurgeComm(hSerial, PURGE_RXCLEAR);


        updateHealthCounter();
        updateBarrelRollCounter();

        BackManager = new backgroundmanager;
        // BackManager->setspace();
        BackManager->bougebackground();

        //proxy->setpos(0, 0);
        qDebug() << "Current working directory: " << QDir::currentPath();
        //QPixmap pixmap("plane.png");
        //hideCursor();
        music.stopMusic();
        music.playMusic("Ocean.wav", 570, 86594);
        loadBarrelRoll->setpos(1725, 980);
        //loadBarrelRoll->start(170);
        loadBarrelRoll->setframe(59);
        loadBarrelRoll->pixmapItem->setScale(0.8);
        loadBarrelRoll->pixmapItem->setZValue(100);
        loadBarrelRoll->pixmapItem->show();




        loadExplosion->setpos(-5, 980);
        //loadExplosion->start(170);
        loadExplosion->setframe(59);
        loadExplosion->pixmapItem->setScale(0.8);
        loadExplosion->pixmapItem->setZValue(100);
        loadExplosion->pixmapItem->show();

        if (version > 0)     //si on a choisi autre chose que le mode seul on initialise le 2e joueur
        {

            listEntites.emplace_back(make_unique<Joueur>((WIDTH / 2) + 50, HEIGHT - 70));   //ajoute le joueur a la liste d'entites
            joueur2 = static_cast<Joueur*>(listEntites.back().get());
            QObject::connect(&tiltresetimerjoueur2, &QTimer::timeout, [=]() {
                resettilt(joueur2);
            });

            coeur2 = new QGraphicsPixmapItem(*ListImages[23]);
            coeur2->setPos(1765, 10);
            coeur2->setScale(0.12);
            coeur2->setZValue(50);
            coeur2->hide();
            GameScene->addItem(coeur2);



            dixVie2 = new QGraphicsPixmapItem(*ListImages[58]);
            dixVie2->setPos(1860, 20);
            dixVie2->setScale(0.45);
            dixVie2->setZValue(50);
            dixVie2->hide();
            GameScene->addItem(dixVie2);
            unitVie2 = new QGraphicsPixmapItem(*ListImages[58]);
            unitVie2->setPos(1885, 20);
            unitVie2->setScale(0.45);
            unitVie2->setZValue(50);
            unitVie2->hide();
            GameScene->addItem(unitVie2);
            joueur2->image->setPixmap(*ListImages[69]);
            joueur2->Originalimage->setPixmap(*ListImages[69]);
            joueur2->DamageImage->setPixmap(*ListImages[70]);
            joueur2->AnimatedSprite->setframe(5);
            joueur2->AnimatedSprite->ChangeJson("barrel_roll2.json");
            joueur2->Proppeller1->ChangeJson("flame.json");
            joueur2->Proppeller1->spritesheet.load("Textures\\Sprites\\flame.png");
            joueur2->Proppeller1->pixmapItem->setScale(0.1);
            joueur2->Proppeller1->pixmapItem->setZValue(5);

            joueur2->AnimatedSprite->spritesheet = *ListImages[69];
            joueur2->AnimatedSprite->pixmapItem->setScale(0.32);
            //joueur2->Proppeller1->pixmapItem->hide();
            GameScene->update();
            //joueur2->enVie = true;
            joueur->posX = (WIDTH / 2) - 50;

            nbJoueur = 2;

            x2 = new QGraphicsPixmapItem(*ListImages[68]);
            x2->setPos(1825, 28);
            x2->setScale(0.35);
            x2->setZValue(50);
            x2->show();
            GameScene->addItem(x2);


            loadBarrelRoll2 = new Sprite("loadingBarrelRollP2.png", "loadingBarrelRollP2.json");
            loadBarrelRoll2->setpos(1775, 910);
            loadBarrelRoll2->start(170);
            loadBarrelRoll2->setframe(59);
            loadBarrelRoll2->pixmapItem->setScale(0.6);
            loadBarrelRoll2->pixmapItem->setZValue(100);
            loadBarrelRoll2->pixmapItem->show();
            GameScene->addItem(loadBarrelRoll2->pixmapItem);
            updateBarrelRollCounter();

            loadExplosion2 = new Sprite("loadingExplosion.png", "loadingExplosion.json");
            //loadExplosion2->setpos(1725, 1020);
            loadExplosion2->setpos(1775, 990);
            loadExplosion2->start(170);
            loadExplosion2->setframe(59);
            loadExplosion2->pixmapItem->setZValue(100);
            loadExplosion2->pixmapItem->setScale(0.6);
            loadExplosion2->pixmapItem->show();
            GameScene->addItem(loadExplosion2->pixmapItem);
            updateExplosionCounter();

            updateHealthCounter();
            loadBarrelRoll->pixmapItem->setScale(0.6);
            loadBarrelRoll->setpos(-5, 910);
            loadBarrelRoll->pixmapItem->setZValue(500);

            loadExplosion->pixmapItem->setScale(0.6);
            loadExplosion->setpos(-5, 1020);
            loadExplosion->pixmapItem->setZValue(500);

            milliers->setPos(WIDTH / 2 - 60, 10);
            centaines->setPos(WIDTH / 2 - 30, 10);
            dizaines->setPos(WIDTH / 2 + 0, 10);
            unites->setPos(WIDTH / 2 + 30, 10);

            joueur->nbVies = 15;
            joueur2->nbVies = 15;
            updateHealthCounter();

            unitVie2->show();
            dixVie2->show();
            coeur2->show();


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
            {
                readSerial(hSerial);
                //PurgeComm(hSerial, PURGE_RXCLEAR);
            }

            gererInput();   //sert a revenir au jeu si on a fait pause
            Sleep(10);
        }
        progressionDifficulte();
        updateEntites();
        gererCollisions();
        enleverEntites();
        updateBarrelRollCounter();
        updateExplosionCounter();
        updateScore();
        //updateAffichage();
        //Sleep(20);

        if (nbJoueur == 1 && joueur == nullptr)
            gameOver = true;
        else if (nbJoueur == 2 && joueur == nullptr && joueur2 == nullptr)
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

void Interface::updateHealthCounter()
{
    if (joueur != nullptr)
    {
        int uni = joueur->nbVies % 10;
        int diz = (joueur->nbVies / 10) % 10;

        if(diz > 0)
        {
            unitVie->setPixmap(*ListImages[58 + uni]);
            unitVie->setPos(130, 20);
            dixVie->setPixmap(*ListImages[58 + diz]);
			dixVie->setPos(105, 20);
			dixVie->show();
		}
        else
        {
            unitVie->setPixmap(*ListImages[58 + uni]);
			unitVie->setPos(105, 20);
            dixVie->setPixmap(*ListImages[58 + diz]);
			dixVie->hide();
        }
    }
    else if (joueur == nullptr)
		unitVie->setPixmap(*ListImages[58]);
    
    if (nbJoueur > 1 && joueur2 != nullptr)
	{
        int uni2 = joueur2->nbVies % 10;
        int diz2 = (joueur2->nbVies / 10) % 10;

        if (diz2 > 0)
        {
            dixVie2->setPos(1860, 20);
            unitVie2->setPos(1885, 20);
            unitVie2->setPixmap(*ListImages[58 + uni2]);
            unitVie2->setPos(1885, 20);
            dixVie2->setPixmap(*ListImages[58 + diz2]);
            dixVie2->setPos(1860, 20);
            dixVie2->show();
        }
        else
        {
            unitVie2->setPixmap(*ListImages[58 + uni2]);
            unitVie2->setPos(1860, 20);
            dixVie2->setPixmap(*ListImages[58 + diz2]);
            dixVie2->hide();
        }
	}
	else if (nbJoueur > 1 && joueur2 == nullptr)
		unitVie2->setPixmap(*ListImages[58]);

}

void Interface::updateBarrelRollCounter()
{
    int numFrame;

    if (joueur != nullptr)
    {
        numFrame = 59;
        if (joueur->coolDownBarrelRoll == 0)
            numFrame = 59;
        else
        {
            numFrame = (float(CD_BARRELROLL - joueur->coolDownBarrelRoll) / float(CD_BARRELROLL)) * 100;
            numFrame = (numFrame * 59) / 100;
            if (numFrame > 59)
                numFrame = 59;
        }

        loadBarrelRoll->setframe(numFrame);
        loadBarrelRoll->pixmapItem->show();
    }
    if (nbJoueur > 1 && joueur2 != nullptr)
    {
        numFrame = 59;
        if (joueur2->coolDownBarrelRoll == 0)
            numFrame = 59;
        else
        {
            numFrame = (float(CD_BARRELROLL - joueur2->coolDownBarrelRoll) / float(CD_BARRELROLL)) * 100;
            numFrame = (numFrame * 59) / 100;
            if (numFrame > 59)
                numFrame = 59;
        }
        loadBarrelRoll2->setframe(numFrame);
        loadBarrelRoll2->pixmapItem->show();
    }

}

void Interface::updateExplosionCounter()
{
    int numFrame;

    if (joueur != nullptr)
    {
        if (explosionTimer == 0)
            numFrame = 59;
        else
        {
            numFrame = (float(900 - explosionTimer) / float(900)) * 100;
            numFrame = (numFrame * 59) / 100;
            if (numFrame > 59)
                numFrame = 59;
        }

        loadExplosion->setframe(numFrame);
        loadExplosion->pixmapItem->show();
    }
	if (nbJoueur > 1 && joueur2!= nullptr)
	{
		numFrame = 59;
		if (explosionTimer == 0)
			numFrame = 59;
		else
		{
			numFrame = (float(900 - explosionTimer) / float(900)) * 100;
			numFrame = (numFrame * 59) / 100;
			if (numFrame > 59)
				numFrame = 59;
		}
		loadExplosion2->setframe(numFrame);
		loadExplosion2->pixmapItem->show();
	}
}

void Interface::updateScore()
{
    int uni = score1 % 10;
    int diz = (score1 / 10) % 10;
    int cent = (score1 / 100) % 10;
    int mill = (score1 / 1000) % 10;

    unites->setPixmap(*ListImages[24 + uni]);
    dizaines->setPixmap(*ListImages[24 + diz]);
    centaines->setPixmap(*ListImages[24 + cent]);
    milliers->setPixmap(*ListImages[24 + mill]);

    /*if (cent == 0)
        centaines->hide();
    else
        centaines->show();*/

    if (mill == 0)
        milliers->hide();
    else
        milliers->show();

}

void Interface::glitchEffect(bool state)
{
	if (state)
	{
        //glitch->start(70);
		glitch->pixmapItem->show();
		blackBackground->show();
	}
	else
	{
		//glitch->stop();
		glitch->pixmapItem->hide();
		blackBackground->hide();
	}
}

void Interface::readSerial(HANDLE hSerial)
{
    //char buffer[56];  // Taille du buffer attendue
    char buffer[65];
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
				dataManette[6] = jsonData["muon"];      //barrel roll

                utiliseManette = true;
            }
            catch (json::parse_error& e) {
                //cerr << "Erreur JSON : " << e.what() << endl;
            }
        }
        //PurgeComm(hSerial, PURGE_RXCLEAR);
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

void Interface::tiltplayerleft(Joueur* player)
{
    if (player->tiltcounter <= 3)
    {
        player->tiltcounter = 3;
        player->AnimatedSprite->setframe(3);
    }
    if (player->tiltcounter > 3)
    {
        //player->AnimatedSprite->start(50);
        player->AnimatedSprite->setframe(player->tiltcounter);
        player->tiltcounter = player->tiltcounter - 1;
    }
}

void Interface::tiltplayerright(Joueur* player)
{
    if (player->tiltcounter >= 7)
    {
        player->AnimatedSprite->setframe(7);
        player->tiltcounter = 7;
    }
    if (player->tiltcounter < 7)
    {
        //player->AnimatedSprite->start(50);
        player->AnimatedSprite->setframe(player->tiltcounter);
        player->tiltcounter = player->tiltcounter + 1;
    }
}

void Interface::resettilt(Joueur* Player)
{

    if (Player == nullptr || Player->enVie != true || Player->AnimatedSprite == nullptr)
    {
        return;
    }
    if (Player->tiltcounter = 5)
    {
        Player->tiltcounter = 5;
        Player->AnimatedSprite->setframe(5);
    }
    if (Player->tiltcounter > 5)
    {
        Player->tiltcounter = Player->tiltcounter - 1;
        Player->AnimatedSprite->setframe(Player->tiltcounter);
    }
    if (Player->tiltcounter < 5)
    {
        Player->tiltcounter = Player->tiltcounter + 1;
        Player->AnimatedSprite->setframe(Player->tiltcounter);
    }
}