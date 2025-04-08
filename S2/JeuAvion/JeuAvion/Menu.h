#ifndef MENU_H
#define MENU_H

#include "Interface.h"
#include "globalobjects.h"
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QFont>
#include <QPixmap>
#include <QPalette>
#include <QDebug>

using namespace std;


class GererMenu : public QGraphicsScene
{

public:
	GererMenu(QObject* parent = nullptr);
	~GererMenu();
	void setFondEcran();

private slots:
	void jouerPeser();
	void audioPeser();
	void classementPeser();
	void quitterPeser();
private:
	QGraphicsTextItem* gameTitle;
	QGraphicsProxyWidget* proxyJouer;
	QGraphicsProxyWidget* proxyAudio;
	QGraphicsProxyWidget* proxyClassement;
	QGraphicsProxyWidget* proxyQuitter;
};

class ChoixMode : public QGraphicsScene
{

public:
	ChoixMode(QObject* parent = nullptr);
	~ChoixMode();
	void setFondEcran();

private slots:
	void soloPeser();
	void coopPeser();
	void revenirPeser();

private:
	QPushButton* soloBouton;
	QPushButton* coopBouton;
	QPushButton* revenirBouton;
	QGraphicsProxyWidget* proxyRevenir;
	QGraphicsProxyWidget* proxyCoop;
	QGraphicsProxyWidget* proxyrevenirBouton;
	QGraphicsProxyWidget* proxySolo;
};

class Audio : public QGraphicsScene
{


public:
	Audio(QObject* parent = nullptr);
	~Audio();
	void setFondEcran();

private slots:
	void sfxPlus();
	void sfxMoins();
	void musiquePlus();
	void musiqueMoins();
	void revenir();

private:
	void revenirPeser();
	QLabel* sfxTitle;
	QLabel* musiqueTitle;
	QLabel* sfxValue;
	QLabel* musiqueValue;
	QPushButton* sfxBoutonUp;
	QPushButton* sfxBoutonDown;
	QPushButton* musiqueBoutonUp;
	QPushButton* musiqueBoutonDown;
	QPushButton* revenirBouton;
	QGraphicsProxyWidget* proxySfxTitle;
	QGraphicsProxyWidget* proxySfxValue;
	QGraphicsProxyWidget* proxyMusiqueTitle;
	QGraphicsProxyWidget* proxyMusiqueValue;
	QGraphicsProxyWidget* proxySfxBoutonUp;
	QGraphicsProxyWidget* proxySfxBoutonDown;
	QGraphicsProxyWidget* proxyMusiqueBoutonUp;
	QGraphicsProxyWidget* proxyMusiqueBoutonDown;
	QGraphicsProxyWidget* proxyRevenirBouton;
};
class Quitter : public QGraphicsScene
{

public:
	Quitter(QObject* parent = nullptr);
	~Quitter();
	void setFondEcran();

private slots:
	void quitter();
	void revenir();

private:
	QGraphicsProxyWidget* proxyConfirmationQuitter;
	QGraphicsProxyWidget* proxyOuiBouton;
	QGraphicsProxyWidget* proxyNonBouton;
	void ouiPeser();
	void nonPeser();
	QPushButton* ouiBouton;
	QPushButton* nonBouton;
	QLabel* confirmationQuitter;
};

class Classement : public QGraphicsScene
{

public:
	Classement(QObject* parent = nullptr);
	~Classement();
	void setFondEcran();
	void ajouter_score_solo();
	void ajouter_score_coop();

private slots:
	void revenir();

private:
	QGraphicsProxyWidget* proxyClassementCoop;
	QGraphicsProxyWidget* proxyClassementSolo;
	QGraphicsProxyWidget* proxyRevenirBouton;
	void revenirPeser();
	void montrer_classement_solo();
	void montrer_classement_coop();
	QPushButton* revenirBouton;
	QTextEdit* classementSolo;
	QTextEdit* classementCoop;
	QString ligneClassementSolo;
	QString ligneClassementCoop;

	struct classement_solo {
		int position;
		string nom;
		int score;
	};

	struct classement_coop {
		int position;
		string equipe;
		int score;
	};

	vector<classement_solo> ScoreSolo;
	vector<classement_coop> ScoreCoop;
};


class Utilisateur : public QGraphicsScene
{


public:
	Utilisateur(QObject* parent = nullptr);
	~Utilisateur();
	void setFondEcran();
	string get_nom();

private slots:
	void suivant();

private:
	QGraphicsProxyWidget* proxyEntrerNom;
	QGraphicsProxyWidget* proxyNomSolo;
	QGraphicsProxyWidget* proxyValider;
	QLineEdit* nomSolo;
	QLabel* entrerNom;
	QPushButton* valider;
	QString nomJoueur;
};





class JouerSolo : public QGraphicsScene
{

public:
	JouerSolo(QObject* parent = nullptr);
	~JouerSolo();
	void setFondEcran();

private slots:
	void commencerSolo();
	void revenir();

private:
	void ouiPeser();
	void nonPeser();
	QPushButton* ouiBouton;
	QPushButton* nonBouton;
	QLabel* confirmationJouer;
	QGraphicsProxyWidget* proxyConfirmationJouer;
	QGraphicsProxyWidget* proxyOuiBouton;
	QGraphicsProxyWidget* proxyNonBouton;
};

class JouerCoop : public QGraphicsScene
{
public:
	JouerCoop(QObject* parent = nullptr);
	~JouerCoop();
	void setFondEcran();

private slots:
	void commencerCoop();
	void revenir();

private:
	QGraphicsProxyWidget* proxyConfirmationJouer;
	QGraphicsProxyWidget* proxyOuiBouton;
	QGraphicsProxyWidget* proxyNonBouton;
	void ouiPeser();
	void nonPeser();
	QPushButton* ouiBouton;
	QPushButton* nonBouton;
	QLabel* confirmationJouer;
};


class Equipe : public QGraphicsScene
{


public:
	Equipe(QObject* parent = nullptr);
	~Equipe();
	void setFondEcran();
	string get_equipe();

private slots:
	void suivant();

private:
	QGraphicsProxyWidget* proxyEntrerEquipe;
	QGraphicsProxyWidget* proxyNomCoop;
	QGraphicsProxyWidget* proxyValider;
	QLineEdit* nomCoop;
	QLabel* entrerEquipe;
	QPushButton* valider;
	QString nomEquipe;
};

#endif