#include "Interface.h"


Interface::Interface()
{
    //initialisation des vairalbes
    score = 0;
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
    //spawnPowerUp = false;
    //nextPup = 0;

    listEntites.emplace_back(make_unique<Joueur>(WIDTH / 2, HEIGHT - 1));   //ajoute le joueur a la liste d'entites
    joueur = static_cast<Joueur*>(listEntites.back().get());                //on recupere le * du joueur de la liste d'entites
}


//gere les inputs du joueur
void Interface::gererInput()
{
    if (pause == false)
    {

        if (GetAsyncKeyState(VK_LEFT) < 0 || GetAsyncKeyState('A') < 0)   //on verifie si la fleche gauche ou D est pressee
        {
            if (joueur->posX > 2)
                joueur->posX -= 2;      //on deplace le joueur de 2 vers la gauche
            else if (joueur->posX > 1)
                joueur->posX--;
        }
        if (GetAsyncKeyState(VK_RIGHT) < 0 || GetAsyncKeyState('D') < 0) {
            if (joueur->posX < WIDTH - 2)
                joueur->posX += 2;
            else if (joueur->posX < WIDTH - 1)
                joueur->posX++;
        }

        if (GetAsyncKeyState(VK_UP) < 0 || GetAsyncKeyState('W') < 0)
            if (joueur->posY > HEIGHT / 10)      //le joueur a acces au 9/10 de l'ecran
                joueur->posY--;

        if (GetAsyncKeyState(VK_DOWN) < 0 || GetAsyncKeyState('S') < 0)
            if (joueur->posY < HEIGHT)
                joueur->posY++;
        if (GetAsyncKeyState(VK_SPACE) < 0)
        {
            if (joueur->shootTimer == 0 && joueur->barrelRollTimer <= 0)    //on tire si on peut
            {
                //listEntites.emplace_back(make_unique<BasicBullet>(joueur->posX + joueur->largeur / 2, joueur->posY - 1, true));
                joueurTir();
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
            }
        }
    }

    if (explosionTimer > 0)
    {
        explosionTimer--;
        explosion();
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
void Interface::joueurTir()
{
    switch (joueur->nbBulletTir)
    {
	case 1:
		listEntites.emplace_back(make_unique<angleBullet>(joueur->posX + joueur->largeur / 2, joueur->posY - 1, 90 + 180, '|', true));
		break;
	case 3:
        for(int i=80;i<110;i+=10)
			listEntites.emplace_back(make_unique<angleBullet>(joueur->posX + joueur->largeur / 2, joueur->posY - 1, i + 180, '|', true));
		break;
    case 5:
		for (int i = 70; i < 120; i += 10)
			listEntites.emplace_back(make_unique<angleBullet>(joueur->posX + joueur->largeur / 2, joueur->posY - 1, i + 180, '|', true));
        break;
    }
}


void Interface::explosion()
{

    if (enExplosion)
    {
        for (auto& e : listEntites)
        {
            if (e->enVie && e->posY >= explosionPosY - 2 && e->posY <= explosionPosY + 2 && !e->isPlayer && e->typeEntite != BOSS)	//on verifie si l'entite est dans une zone d'explosion qui avance vers le haut de l'ecran
            {
                e->enVie = false;
                //score += customPoints(e->getTypeEnnemi());
            }
        }
    }

    if (explosionPosY > 0)
        explosionPosY--;
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

    if (score < 600)
    {

        if (enemySpawnTimer >= 100 || cbVivant() < 5)          //on fait spawn une vague d'ennemis a toutes les 70 frames
        {
            enemySpawn(1, BASIC);   //on fait spawn 3 ennemis a chaque vague
            enemySpawn(1, ARTILLEUR);
            //enemySpawn(1, ZAPER);
            //enemySpawn(1, AIMBOT);
            //enemySpawn(2, SIDEBOMBER);
            // enemySpawn(1, DIVEBOMBER);
            //enemySpawn(1, TANK);

            if (!spawnPup)
            {
                //enemySpawn(1, BOSS2_MAIN);
                spawnPup = true;
				powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2 -5);
                powerupSpawn(1, ADDBULLETS, WIDTH / 2, HEIGHT / 2);
            }

            enemySpawnTimer = 0;        //on reset le timer pour pouvoir spanw la prochaine vague d'ennemis
        }
    }
    if (score >= 600 && score < 1300)
    {
        if (enemySpawnTimer >= 25)          //on fait spawn une vague d'ennemis a toutes les 60 frames
        {
            //enemySpawn(3, BASIC);   //on fait spawn 4 ennemis a chaque vague
            enemySpawn(5, DIVEBOMBER);
            enemySpawnTimer = 0;        //on reset le timer pour pouvoir spanw la prochaine vague d'ennemis
        }
    }
    if (score >= 1300 && score < 2000)
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
    if (score >= 2000 && !boss1Spawned)
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

                memScore = score + 200;     //on garde le score en memoire lorsque le boss apparait, on y ajoute 250 pour le score du boss afin de connaitre le score qd le boss meurt afin de faire apparaitre les prochains ennemis
                bossWaitTimer = 0;
            }
            else
                bossWaitTimer++;
        }
    }
    if (score >= memScore && score <= memScore + 850 && boss1Spawned)   //on fait spawn des ennemis apres que le boss soit mort 
    {

        if (bossWaitTimer > 100)
        {
            if (enemySpawnTimer >= 150 || cbVivant() < 6)
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
    if (score >= memScore + 850 && score <= memScore + 1600 && boss1Spawned)   //on fait spawn des ennemis apres que le boss soit mort 
    {
        if (enemySpawnTimer >= 5)
        {
            enemySpawn(1, DIVEBOMBER);
            enemySpawnTimer = 0;
            bossWaitTimer = 0;
        }
    }
    if (score >= memScore + 1600 && score <= memScore + 2400 && boss1Spawned)
    {
        if (enemySpawnTimer >= 150 || cbVivant() < 7)
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
    if (score >= memScore + 2400 && !boss2Spawned)
    {
        if (cbVivant() == 0)
        {

            if (bossWaitTimer > 200)	 //on attend un certain temps apres la mort du dernier ennemi avant de spawn le boss
            {
                enemySpawn(1, BOSS2_MAIN);
                boss2Spawned = true;

                memScore = score + 200;     //on garde le score en memoire lorsque le boss apparait, on y ajoute 250 pour le score du boss afin de connaitre le score qd le boss meurt afin de faire apparaitre les prochains ennemis
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
    static bool spawnPowerUp = true;

    for (auto& e : listEntites)     //on parcourt la liste d'entites
    {
        if (e->enVie)
        {
            e->getPosJoueur(joueur->posX, joueur->posY);    //on donne la position du joueur a chaque entite, va etre utliser pour les choses a tete chercheuse etc.
            e->update();    //on met a jour l'entite

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
                if (e->nbVies % 70 == 0 && spawnPowerUp)
                {
                    powerupSpawn(1, ADDLIFE, e->posX + e->largeur / 2, e->posY + e->hauteur / 2);
                    spawnPowerUp = false;
                }
                else if (e->nbVies % 70 != 0)
                    spawnPowerUp = true;

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
        bufferBulletsUpdate.emplace_back(make_unique<angleBullet>(x, y, angleTirBoss + i,'o', false));

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

    for (auto& e : listEntites)
    {
        if (e->enVie)
        {
            if (e->enCollision(joueur->posX, joueur->posY) && joueur->invincibleTimer <= 0 && joueur->barrelRollTimer <= 0 && !e->isPlayer)     //on verifie si un entite entre en collision avec le joueur et verifie que e n'est pas joueur
            {
                if ((e->typeEntite == ENNEMI || e->typeEntite == BOSS) && e->collisionJoueur == false)
                {
                    joueur->perdVie(2);	 //le joueur perd 2 vies si il entre en collision avec un ennemi
                    joueur->invincible = true;     //le joueur est invincible pour un court moment apres

                    if (!joueur->enVie)
                        gameOver = true;

                    e->collisionJoueur = true;
                }
                else if (e->typeEntite == BULLET && e->collisionJoueur == false && !e->bulletAllie)     //si le joueur entre en collision avec une bullet ennemi sans etre en barrel roll il perd une vie
                {
                    joueur->perdVie(1);    //le joueur perd 1 vie si il entre en collision avec une bullet ennemi et s'il est pas invincible
                    joueur->invincible = true;     //le joueur est invincible pour un court moment apres

                    if (!joueur->enVie)
                        gameOver = true;

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
                        if (e2->enVie && e2->enCollision(e->posX, e->posY) && e2->symbole != e->symbole && e2->typeEntite != POWERUP)       // si qqlch entre en collision avec la bullet allie et le e->symbole est pour pas que la bullet entre en collision avec elle meme 
                        {
                            if (e2->ammoType == FRAGMENTING && e2->typeEntite == BULLET && !e2->bulletAllie)      //si c'est un fragmenting bullet d'unennemi
                                for (int i = -1; i < 2; i++)	//commence a -1 pour que le premier fragment commence a la gauche de la bullet
                                    bufferBullets.emplace_back(make_unique<BasicBullet>(e2->posX + i, e2->posY + 1, false));

                            e2->perdVie(1);
                            if (e2->nbVies != 0)       //si l'ennemi n'a pas de vie comme
                                e->enVie = false;   //la bullet meurt si elle entre en collision avec un ennemi

                            if (!e2->enVie && (e2->typeEntite == ENNEMI || e2->typeEntite == BOSS))
                            {
                                score += customPoints(e2->getTypeEnnemi());
                                if (score % 500 <= 10 && score > 100)      //on fait spawn un powerup a chaque 500 points
                                {
                                    powerupSpawn(1, ADDLIFE, e2->posX + e2->largeur / 2, e2->posY + e2->hauteur / 2);       //on fait spawn un powerup a la position de l'ennemi
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
        return 100;
        break;
    case BOSS1_SIDE:
        return 50;
        break;
    case SIDEBOMBER:
        return 15;
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
    score = 0;
    explosionTimer = 0;
    enExplosion = false;
    cdExplosion = 0;
    boss1Spawned = false;
    bossWaitTimer = 0;
    memScore = 1200;
    bossMusicStart = false;
    bossSpawnSound = false;

}


//met a jour l'affichage de la console 
void Interface::updateAffichage()
{
    wchar_t buffer[HEIGHT + 4][WIDTH + 2];  // +3 pour les bordures et le score, +2 pour les bordures
    wchar_t progressExplosion[12];	//buffer pour afficher progression de l'explosion
    wchar_t progressBarrelRoll[12];	//buffer pour afficher progression du barrel roll
    float nbSymboleExplosion = 0;  //pour le nombre de symboles a afficher dans la progression de l'explosion
    float nbSymboleBarrelRoll = 0;
    wstring texte;  //on cree un string pour afficher le score, le nombre de vies et autres textes


    // Remplir le tampon avec des espaces (effacer l'écran)
    for (int y = 0; y < HEIGHT + 4; y++) {
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
        nbSymboleBarrelRoll = 10;
    else
    {
        nbSymboleBarrelRoll = ((float)(CD_BARRELROLL - joueur->coolDownBarrelRoll) / (float)CD_BARRELROLL) * 10;
        if (nbSymboleBarrelRoll > 10)
            nbSymboleBarrelRoll = 10;
    }

    for (int i = 0; i < (int)nbSymboleBarrelRoll; i++)
        progressBarrelRoll[i + 1] = L'#';

    texte = L"Barrel Roll: ";
    for (int i = 0; i < texte.size(); i++)   //on ajoute le score au buffer
        buffer[HEIGHT + 2][i + posCurseur] = texte[i];

    for (int i = 0; i < 12; i++)
        buffer[HEIGHT + 2][i + texte.size() + posCurseur] = progressBarrelRoll[i];


    // Afficher le score
    if (gameOver)
        texte = L"Game Over!  Score: " + to_wstring(score);
    else
        texte = L"Score: " + to_wstring(score) + L"   Lives: " + to_wstring(joueur->nbVies);

    for (size_t i = 0; i < texte.size(); i++)   //on ajoute le score au buffer
        buffer[HEIGHT + 3][i] = texte[i];

    // on affiche chaque ligne du buffer
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int y = 0; y < HEIGHT + 4; y++)
    {
        COORD bufferCoord = { 0, static_cast<SHORT>(y) };
        DWORD charsWritten;

        WriteConsoleOutputCharacterW(hConsole, buffer[y], WIDTH + 2, bufferCoord, &charsWritten);       //on ecrit chaque ligne du buffer
    }
}


//enleve les entites mortes de la liste d'entites
void Interface::enleverEntites()
{
    for (int i = 0; i < listEntites.size(); i++)
    {
        if (!listEntites[i]->enVie)
        {
            listEntites.erase(listEntites.begin() + i);
            i--;
        }
    }
}


//execution du jeu
void Interface::executionJeu()
{
    hideCursor();
    music.stopMusic();
    music.playMusic("OceanWorld.wav", 0, 117000);
    while (!gameOver)
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
        Sleep(20);

    }
    restart();

    Sleep(1500);
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