#include "Entites.h"

Entite::Entite(float x, float y, char symb, int largeurEntite, int hauteurEntite)
{
	//donne des valeurs par defaut aux variables qui vont etre redefinies dans les classes enfant
	posX = x;
	posY = y;
	hauteur = hauteurEntite;
	largeur = largeurEntite;
	symbole = symb;
	enVie = true;
	collisionJoueur = false;
	shootCooldown = -1;
	shootTimer = -1;
	moveTimer = 0;
	nbVies = 1;
	bulletAllie = false;
	typeEntite = ENNEMI;
	xJoueur = 0;
	yJoueur = 0;
	xJoueur2 = 0;
	yJoueur2 = 0;
	p1EnVie = true;
	p2EnVie = true;
	//nbJoueurs = 1;
	shoots = true;
	ammoType = NORMAL;
	invincible = false;
	invincibleTimer = 0;
	isPlayer = false;
	barrelRollTimer = 0;
	power_up = ADDLIFE;		//par defaut les powerups donnent des vies

}



bool Entite::enCollision(int px, int py)
{
	if (px >= posX - 1 && px <= posX + largeur + 1 && py >= posY && py < (posY + hauteur))       // on fait une collision si les entites sont a la meme position (+ - 1 pour amelirer la detection)
		return 1;

	return 0;
}

//recoit la position des joueurs par interface.cpp pour que les entites schent toujours ou sont les joueurs
void Entite::getPosJoueurs(float x1, float y1, bool p1Alive, float x2, float y2, bool p2Alive)
{
	xJoueur = x1;
	yJoueur = y1;
	xJoueur2 = x2;
	yJoueur2 = y2;
	p1EnVie = p1Alive;
	p2EnVie = p2Alive;

}

typeEnnemis Entite::getTypeEnnemi()		// va etre redefinie dans la classe ennemi pour retourner le type d'ennemi
{
	return BASIC;	//retourne BASIC par defaut
}

void Entite::perdVie(int nbVie)
{
	for (int i = 0; i < nbVie; i++)     //joueur perd 2 vies si il entre en collision avec un ennemi   // pour peut ajouter un nb de degats a chaque ennemi
	{
		if (nbVies > 0 && enVie && !invincible)
		{
			nbVies--;
			if (nbVies == 0)
				enVie = false;
		}
	}
}

//******************************** classe joueur ***********************************

Joueur::Joueur(float x, float y) : Entite(x, y, '^', 1, 1)  //on set les valeurs par defaut pour le joueur
{
	hauteur = 250/4; //Diviser par 4 a cause du scale de 0.25 de l'image du joueur
	largeur = 290/4; //Diviser par 4 a cause du scale de 0.25 de l'image du joueur
	nbVies = 10;
	attkDmg = 1;
	vitesse = 1;
	shootCooldown = 6;
	nbBulletTir = 1;
	shootTimer = 0;
	bulletAllie = true;
	typeEntite = JOUEUR;
	//barrelRollTimer = 0;
	barrelRoll = false;
	coolDownBarrelRoll = 0;
	isPlayer = true;
	barrelRollTimer = 0;

}


void Joueur::update()
{

	if (shootTimer > 0)
		shootTimer--;

	if (barrelRoll)					//si le joueur fait un barrel roll
	{
		barrelRoll = false;
		barrelRollTimer = 30;		//temps du barrel roll
		//invincible = true;
		symbole = '&';
		coolDownBarrelRoll = CD_BARRELROLL;		// cooldown du barrel roll
	}
	else if (invincible)		//NE MONTRE PAS LE SYMBOLE DE $ SI ININVINCILE APRES ETRE TOUCHE
	{
		invincible = false;
		invincibleTimer = 50;
		symbole = '$';

	}
	else if (barrelRollTimer <= 0 && invincibleTimer <= 0)	//si le barrel roll est fini
	{
		symbole = '^';
	}

	if (coolDownBarrelRoll > 0)
		coolDownBarrelRoll--;

	if (barrelRollTimer > 0)
		barrelRollTimer--;

	if (invincibleTimer > 0)       //puique move timer augmente a l'infini, on le reset a 0 avant qu'il ne monte trop haut pour eviter des erreurs
		invincibleTimer--;

	//if (shootTimer > 0)
		//shootTimer--;
	player1->setPos(posX, posY);// update image du joueur
}


//******************************** classe ennemi ***********************************

Ennemi::Ennemi(float x, float y) : Entite(x, y, 'X', 1, 1)
{
	//set des valeurs par defaut pour les ennemis a etre redefinies dans les classes enfant
	attkDmg = 1;
	vitesse = 1;
	direction = rand() % 2; ; // 0 A gauche, 1 a droite
	shootCooldown = 50;
	shootTimer = -1;
	nbVies = 1;
	moveTimer = 0;
	bulletAllie = false;
	typeEntite = ENNEMI;
	typeEnnemi = BASIC;
	shoots = true;
	posRand = 0;
}

typeEnnemis Ennemi::getTypeEnnemi()
{
	return typeEnnemi;
}

BasicEnnemi::BasicEnnemi(float x, float y) : Ennemi(x, y)
{
	symbole = 'W';
	nbVies = 3;
	shootCooldown = 100;   // x frames avant de tirer donc plus gros chiffre = tir plus lent
	//shootTimer = rand() % shootCooldown;   //on set le timer de tir a un nombre aleatoire entre 0 et le cooldown de tir
	typeEnnemi = BASIC;
	hauteur = 2;
	largeur = 4;
	moveTimer = rand() % shootCooldown;   //on set le timer de mouvement a un nombre aleatoire entre 0 et le cooldown de tir pour que les ennemis tirent a des moments differents

	//pngImg.load("plane.png");
	//image = new QGraphicsPixmapItem(pngImg);

}

void BasicEnnemi::update()
{
	if (moveTimer % 5 == 0)         //a toute les 5 update on peut bouger en X 
	{
		if (posX <= 1 || posX + largeur >= WIDTH - 1)
			direction = 1 - direction; // Change de Direction

		if (direction == 0)
			posX -= 1;
		else
			posX += 1; // Bouger a gauche ou a droite
	}

	if (moveTimer % 8 == 0)   //a toute les 8 update on peut bouger en Y
		posY++;

	if (moveTimer >= 100)       //puique move timer augmente a l'infini, on le reset a 0 avant qu'il ne monte trop haut pour eviter des erreurs
		moveTimer = 0;

	if (posY >= HEIGHT)     //si l'ennemi atteint le bas de l'ecran is meurt
		enVie = false;

	moveTimer++;
}


DiveBomber::DiveBomber(float x, float y) : Ennemi(x, y)
{
	symbole = 'V';
	nbVies = 3;
	typeEnnemi = DIVEBOMBER;
	hauteur = 4;
	largeur = 2;
	shoots = false;

	if (p1EnVie == true && p2EnVie == true)
		joueurRand = rand() % 2;	//choisi un joueur en vie aleatoirement pour le suivre
	else if (!p1EnVie && p2EnVie)
		joueurRand = 1;
	else if (p1EnVie && !p2EnVie)
		joueurRand = 0;
	else
		joueurRand = 0;

}


//le diveBomber est kamikaze qui va directement vers le joueur
void DiveBomber::update()
{
	if (moveTimer % 2 == 0)         //on peut ajuster la vitesse en x du diveBomber
	{
		if (p1EnVie && !p2EnVie)		//si juste p1 est viant
		{
			if (posX < xJoueur)
				posX++;
			else if (posX > xJoueur)
				posX--;
		}
		else if (p1EnVie && p2EnVie)
		{
			//choisi un joueur en vie aleatoirement pour le suivre
			if (joueurRand == 0)
			{
				if (posX < xJoueur)
					posX++;
				else if (posX > xJoueur)
					posX--;
			}
			else if (joueurRand == 1)
			{
				if (posX < xJoueur2)
					posX++;
				else if (posX > xJoueur2)
					posX--;
			}
		}
		else if (!p1EnVie && p2EnVie)
		{
			if (posX < xJoueur2)
				posX++;
			else if (posX > xJoueur2)
				posX--;
		}
	}
	if (moveTimer % 1 == 0)         //on peut ajuster la vitesse du diveBomber
	{
		posY++;
	}
	if (moveTimer >= 100)       //puique move timer augmente a l'infini, on le reset a 0 avant qu'il ne monte trop haut pour eviter des erreurs
		moveTimer = 0;
	if (posY >= HEIGHT)     //si l'ennemi atteint le bas de l'ecran is meurt
		enVie = false;
	moveTimer++;
}

Tank::Tank(float x, float y) : Ennemi(x, y)
{
	symbole = '@';
	nbVies = 10;
	typeEnnemi = TANK;
	hauteur = 1;
	largeur = 9;
	shoots = false;
	posRand = rand() % 4;   //donne une valeur qu'on va ajouter a son y pour pas qu'ils soient tous alignes
}

void Tank::update()
{
	if (moveTimer % 5 == 0)
	{
		if (posY <= HEIGHT / 3 + posRand)
			posY++;
	}
	if (moveTimer % 50 == 0)
	{
		if (posX <= 1 || posX + largeur >= WIDTH - 1)
			direction = 1 - direction; // Change de Direction
		if (direction == 0)
			posX -= 1;
		else
			posX += 1; // Bouger a gauche ou a droite
	}
	if (moveTimer >= 100)       //puique move timer augmente a l'infini, on le reset a 0 avant qu'il ne monte trop haut pour eviter des erreurs
		moveTimer = 0;
	moveTimer++;
}



Artilleur::Artilleur(float x, float y) : Ennemi(x, y)
{
	shoots = true;
	symbole = 'H';
	nbVies = 3;
	typeEnnemi = ARTILLEUR;
	hauteur = 2;
	largeur = 2;
	shootCooldown = 80;   // x frames avant de tirer donc plus gros chiffre = tir plus lent
	posRand = rand() % 6;   //donne une valeur qu'on va ajouter a son y pour pas qu'ils soient tous alignes
	ammoType = FRAGMENTING;
}

void Artilleur::update()
{
	if (posY <= (HEIGHT / 15) + posRand && moveTimer % 8 == 0)
		posY++;

	if (moveTimer % 50 == 0)
	{
		if (posX <= 1 || posX + largeur >= WIDTH - 1)
			direction = 1 - direction; // Change de Direction
		if (direction == 0)
			posX -= 1;
		else
			posX += 1; // Bouger a gauche ou a droite
	}

	moveTimer++;
}

Zaper::Zaper(float x, float y) : Ennemi(x, y)
{
	shoots = true;
	symbole = '?';
	nbVies = 3;
	typeEnnemi = ZAPER;
	hauteur = 2;
	largeur = 5;
	shootCooldown = 1;
	ammoType = LASER;
	//moveTimer = 0;		//poru qu'ils tirent tous en meme temps qd ils appaissent

}

void Zaper::update()
{
	if (posY <= HEIGHT / 10 && moveTimer % 8 == 0)
		posY++;

	if (moveTimer % 25 == 0)
	{
		if (posX <= 1 || posX + largeur >= WIDTH - 1)
			direction = 1 - direction; // Change de Direction
		if (direction == 0)
			posX -= 1;
		else
			posX += 1; // Bouger a gauche ou a droite
	}

	if (moveTimer % 125 == 0)   //determine le temps on et off du laser
	{
		if (!shoots)
			shoots = true;
		else if (shoots)
			shoots = false;
	}

	moveTimer++;
	if (moveTimer >= 500)
		moveTimer = 0;
}

Aimbot::Aimbot(float x, float y) : Ennemi(x, y)
{
	moveTimer = rand() % shootCooldown;   //on set le timer de mouvement a un nombre aleatoire entre 0 et le cooldown de tir pour que les ennemis tirent a des moments differents
	shoots = true;
	symbole = 'X';
	nbVies = 3;
	typeEnnemi = AIMBOT;
	hauteur = 2;
	largeur = 3;
	shootCooldown = 50;   // a toute les x frames l'entite va tirer
	posRand = rand() % 6;   //donne une valeur qu'on va ajouter a son y pour pas qu'ils soient tous alignes
	ammoType = HOMING;
}

void Aimbot::update()
{
	if (posY <= (HEIGHT / 20) + posRand && moveTimer % 8 == 0)
		posY++;

	if (moveTimer % 50 == 0)
	{
		if (posX <= 1 || posX + largeur >= WIDTH - 1)
			direction = 1 - direction; // Change de Direction
		if (direction == 0)
			posX -= 1;
		else
			posX += 1; // Bouger a gauche ou a droite
	}

	moveTimer++;
}


Boss1::Boss1(float x, float y) : Ennemi(x, y)
{
	symbole = 'B';
	nbVies = 65;
	typeEntite = BOSS;
	typeEnnemi = BOSS1_MAIN;
	ammoType = HOMING;
	hauteur = 8;
	largeur = 15;
	shootCooldown = 50;   // x frames avant de tirer donc plus gros chiffre = tir plus lent
	shoots = true;
}

void Boss1::update()
{
	if (moveTimer % 5 == 0)
	{
		if (posY <= HEIGHT / 15)
			posY++;
	}
	if (moveTimer % 5 == 0)
	{
		if (posX <= 1 || posX + largeur >= WIDTH - 1)
			direction = 1 - direction; // Change de Direction
		if (direction == 0)
			posX -= 1;
		else
			posX += 1; // Bouger a gauche ou a droite
	}
	if (moveTimer >= 100)       //puique move timer augmente a l'infini, on le reset a 0 avant qu'il ne monte trop haut pour eviter des erreurs
		moveTimer = 0;
	moveTimer++;
}

Boss1Side::Boss1Side(float x, float y) : Ennemi(x, y)
{
	symbole = 'B';
	nbVies = 45;
	typeEntite = BOSS;
	typeEnnemi = BOSS1_SIDE;
	hauteur = 3;
	largeur = 8;
	shoots = false;
	shootCooldown = 1;
	ammoType = LASER;
	firstEntry = true;

	if ((rand() % 3) == 0)		//pour que les side boss side tirent a des moments differents cahque foais qu'il spawn
		shootTiming = true;
	else
		shootTiming = false;

}


void Boss1Side::update()
{
	if (moveTimer % 5 == 0 && posY <= 13)
		posY++;
	else if (posY >= 13)
	{
		if (firstEntry)
		{
			shoots = shootTiming;
			firstEntry = false;
		}

		if (moveTimer % 2 == 0)         //a toute les 5 update on peut bouger en X 
		{
			if (posX <= 1 || posX + largeur >= WIDTH - 1)
				direction = 1 - direction; // Change de Direction

			// Bouger a gauche ou a droite
			if (direction == 0)
				posX -= 1;
			else
				posX += 1;
		}

		if (moveTimer % 100 == 0)   //determine le temps on et off du laser
		{
			if (!shoots)
				shoots = true;
			else if (shoots)
				shoots = false;
		}
	}

	if (moveTimer >= 500)       //puique move timer augmente a l'infini, on le reset a 0 avant qu'il ne monte trop haut pour eviter des erreurs
		moveTimer = 0;

	moveTimer++;
}

SideBomber::SideBomber(float x, float y) : Ennemi(x, y)
{
	symbole = 'S';
	nbVies = 2;
	typeEnnemi = SIDEBOMBER;
	hauteur = 1;
	largeur = 1;	//on change la largeur au fur et a mesur qu'il entre 
	shoots = false;

	if (posX == 1)
		side = true;
	else
		side = false;
}


void SideBomber::update()
{

	if (moveTimer % 1 == 0)         //on peut ajuster la vitesse du diveBomber
	{
		if (side)
		{
			if (posX < WIDTH - 5)
			{

				if (largeur < 6)		//on augmente la largeur du bomber jusqu'a 6
					largeur++;
				else
					posX++;		//its weird but needed dont touch
			}
			else if (posX >= WIDTH - 5)
			{
				posX++;
				largeur--;
				if (largeur <= 0)
					enVie = false;
			}


		}
		else
		{
			if (posX > 0)
			{
				posX--;
				if (largeur < 6)		//on augmente la largeur du bomber jusqu'a 6
					largeur++;
			}
			if (posX <= 0)
			{
				largeur--;
				if (largeur <= 0)
					enVie = false;

			}
		}

	}
	if (moveTimer >= 100)       //puique move timer augmente a l'infini, on le reset a 0 avant qu'il ne monte trop haut pour eviter des erreurs
		moveTimer = 0;

	moveTimer++;
}

Boss2::Boss2(float x, float y) : Ennemi(x, y)
{
	symbole = '%';
	nbVies = 200;
	typeEntite = BOSS;
	typeEnnemi = BOSS2_MAIN;
	ammoType = ANGLE;
	hauteur = 6;
	largeur = 10;
	shootCooldown = 5;   // x frames avant de tirer donc plus gros chiffre = tir plus lent
	shoots = true;
	angle = 0;
	rayonMouv = 7;		//va faire un cercle de rayon 7
}


void Boss2::update()
{
	if (moveTimer % 1 == 0)
	{
		posX = WIDTH / 2 + (rayonMouv * cos((angle * 2 * PI) / 360));
		posY = HEIGHT / 2 + (rayonMouv / 2 * sin((angle * 2 * PI) / 360));

		angle++;			//vitesse angulaire determine ici
	}
	if (angle >= 360)
		angle = 0;
	if (moveTimer >= 500)
		moveTimer = 0;
	moveTimer++;
}

Shotgunner::Shotgunner(float x, float y) : Ennemi(x, y)
{
	symbole = 'J';
	nbVies = 3;
	typeEnnemi = SHOTGUNNER;
	hauteur = 3;
	largeur = 3;
	shoots = true;
	shootCooldown = 50;   // a toute les x frames l'entite va tirer
	ammoType = ANGLE;
	rayonMouv = 30;		//va faire un cercle de rayon 6 autour du joueur
	angle = 270;
	distance = 0;
	orbiting = false;
}


void Shotgunner::update()
{
	// l'entite va descendre et commencer a faire des cercles autour du joueur en le tirant avec son shotgun

	distance = sqrt(pow(xJoueur - posX, 2) + pow(yJoueur - posY, 2));				//calcul de la distance entre le joueur et l'entite avec pythagore

	if (posY < yJoueur - rayonMouv / 2 && orbiting == false)		//tant que le shotgunner n'est pas dans le rayon de mouvement il descend
	{
		if (moveTimer % 2 == 0)
		{
			posY++;
		}

	}
	else			//quand il est dans le rayon de mouvement il commence a faire des cercles autour du joueur
	{
		if (orbiting == false)
		{
			orbiting = true;
		}
		//je dois determiner l'angle du shotgonnuer lorsqu'il entre dans le range du joueur
		if (moveTimer % 1 == 0)
		{
			posX = xJoueur + (rayonMouv * cos((angle * 2 * PI) / 360));			//meme maniere qu'on a fait pour faire bouger le boss2 en cercle
			posY = yJoueur + (rayonMouv / 2 * sin((angle * 2 * PI) / 360));
			angle += 2;			//vitesse angulaire determine 
		}
		if (angle >= 360)
			angle = 0;
	}

	if (posX < 1)
		posX = 1;
	else if (posX > WIDTH - 1)
		posX = WIDTH - 1;
	if (posY < 1)
		posY = 1;
	else if (posY > HEIGHT - 2)
		posY = HEIGHT - 2;

	moveTimer++;
}


//******************************** classe bullet ***********************************

Bullet::Bullet(float x, float y, bool isPlayerBullet) : Entite(x, y, '|', 1, 1)
{
	//set des valeurs par defaut pour les bullets a etre redefinies dans les classes enfant
	nbVies = 0;
	bulletAllie = isPlayerBullet;
	typeEntite = BULLET;
	ammoType = NORMAL;
}

BasicBullet::BasicBullet(float x, float y, bool isPlayerBullet) : Bullet(x, y, isPlayerBullet)
{
	symbole = '|';
	ammoType = NORMAL;
	hauteur = 1;
	largeur = 1;
	sfx.playSFX("basicbullet.wav"); // Jouer son du basic bullet
	
	gif = new QMovie("Textures\\bullets\\basicbullet.gif");
	label = new QLabel;

	label->setMovie(gif);
	gif->start();
	label->setAttribute(Qt::WA_TranslucentBackground);
	GameScene->addWidget(label);
}

void BasicBullet::update()
{
	if (bulletAllie)
	{
		if (moveTimer % 1 == 0) {       //on va pouvoir changer la vitesse de la bullet dependant du modulo
			posY-= 10;
			if (posY < 0)
				enVie = false;
		}
	}
	else    //c'est une bullet ennemi
	{
		if (moveTimer % 1 == 0) {       //on peut aussi ajuster la vitesse des bullets ennemis
			posY+=10;
			if (posY >= HEIGHT + 1)
				enVie = false;
		}
	}
	moveTimer++;

	if (moveTimer >= 100)
		moveTimer = 0;

	label->move(posX, posY);
}

FragmentingBullet::FragmentingBullet(float x, float y, bool isPlayerBullet) : Bullet(x, y, isPlayerBullet)
{
	symbole = 'o';
	ammoType = FRAGMENTING;
	hauteur = 1;
	largeur = 2;
	nbVies = 1;
}

void FragmentingBullet::update()
{
	if (moveTimer % 1 == 0)        //on peut aussi ajuster la vitesse des bullets ennemis
		posY++;

	if (posY >= HEIGHT + 1)
		enVie = false;

}

Laser::Laser(float x, float y, bool isPlayerBullet) : Bullet(x, y, isPlayerBullet)
{
	symbole = '~';
	ammoType = LASER;
	largeur = 1;
	if (!isPlayerBullet)
		hauteur = HEIGHT - posY + 1;

}


void Laser::update()
{
	if (posY >= HEIGHT - hauteur)
		enVie = false;

}

Homing::Homing(float x, float y, bool isPlayerBullet) : Bullet(x, y, isPlayerBullet)
{
	symbole = 'V';
	ammoType = HOMING;
	hauteur = 2;
	largeur = 1;
	nbVies = 2;

	if (p1EnVie == true && p2EnVie == true)
		joueurRand = rand() % 2;	//choisi un joueur en vie aleatoirement pour le suivre
	else if (!p1EnVie && p2EnVie)
		joueurRand = 1;
	else if (p1EnVie && !p2EnVie)
		joueurRand = 0;
	else
		joueurRand = 0;
}


void Homing::update()
{
	if (moveTimer % 1 == 0)         //on peut ajuster la vitesse en x du missile
	{
		if (p1EnVie && !p2EnVie)
		{

			if (posX < xJoueur)
				posX++;
			else if (posX > xJoueur)
				posX--;
		}
		else if (p1EnVie && p2EnVie)
		{
			//choisi un joueur en vie aleatoirement pour le suivre
			if (joueurRand == 0)
			{
				if (posX < xJoueur)
					posX++;
				else if (posX > xJoueur)
					posX--;
			}
			else if (joueurRand == 1)
			{
				if (posX < xJoueur2)
					posX++;
				else if (posX > xJoueur2)
					posX--;
			}
		}
		else if (!p1EnVie && p2EnVie)
		{
			if (posX < xJoueur2)
				posX++;
			else if (posX > xJoueur2)
				posX--;
		}
	}
	if (moveTimer % 1 == 0)         //on peut ajuster la vitesse du missile
	{
		posY++;
	}


	if (moveTimer >= 100)       //puique move timer augmente a l'infini, on le reset a 0 avant qu'il ne monte trop haut pour eviter des erreurs
		moveTimer = 0;
	if (posY >= HEIGHT)     //si le missile atteint le bas de l'ecran is meurt
		enVie = false;
	moveTimer++;
}

angleBullet::angleBullet(float x, float y, int angle, char symb = 'o', bool isPlayerBullet = false) : Entite(x, y, symb, 1, 1)
{
	typeEntite = BULLET;
	ammoType = ANGLE;
	hauteur = 1;
	largeur = 1;
	nbVies = 0;
	direction = angle;		//0 a 360 pour les directions possibles
	bulletAllie = isPlayerBullet;
	sfx.playSFX("basicbullet.wav"); // Jouer son du basic bullet
}


void angleBullet::update()
{
	if (moveTimer % 1 == 0)        //on peut aussi ajuster la vitesse des bullets ennemis
	{
		if (bulletAllie)
		{
			posX += cos((direction * 2 * PI) / 360) * 1.2;
			posY += sin((direction * 2 * PI) / 360) * 1.2;
		}
		else
		{
			posX += cos((direction * 2 * PI) / 360);
			posY += sin((direction * 2 * PI) / 360) / 2;
		}
	}

	if (posY >= HEIGHT + 1 || posY <= 0 || posX >= WIDTH || posX <= 0)
		enVie = false;

	moveTimer++;

	if (moveTimer >= 100)
		moveTimer = 0;
}

//******************************** classe obstacle ***********************************

Obstacle::Obstacle(float x, float y, int longueur, int larg, int vie) : Entite(x, y, '#', 3, 1)
{
	nbVies = vie;
}

void Obstacle::update()
{
	if (nbVies <= 0)
		enVie = false;
}

//******************************** classe powerup ***********************************

PowerUp::PowerUp(float x, float y, typePowerUp type) : Entite(x, y, '$', 2, 2)
{
	typeEntite = POWERUP;
	power_up = type;
	symbole = '$';
	hauteur = 2;
	largeur = 3;
}

void PowerUp::update()
{
	if (moveTimer % 30 == 0 && posY < HEIGHT)
		posY++;
	else if (posY >= HEIGHT)
		enVie = false;

	moveTimer++;
}

AddLife::AddLife(float x, float y) : PowerUp(x, y, ADDLIFE)
{
	symbole = '+';
	power_up = ADDLIFE;
}

AddBullet::AddBullet(float x, float y) : PowerUp(x, y, ADDBULLETS)
{
	symbole = 'a';
	power_up = ADDBULLETS;
}

