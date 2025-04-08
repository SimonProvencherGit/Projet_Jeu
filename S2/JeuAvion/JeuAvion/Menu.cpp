#include "Menu.h"




//// CHARGEMENT DES ASSETS /////

void loadimages() { //Initialisation de toute les images.
	ListImages[0] = make_unique<QPixmap>();
	ListImages[0]->load("Textures\\Ennemis\\BasicEnnemi.png");
	ListImages[1] = make_unique<QPixmap>();
	ListImages[1]->load("Textures\\Ennemis\\BasicEnnemi-d.png");
	ListImages[2] = make_unique<QPixmap>();
	ListImages[2]->load("Textures\\Ennemis\\artilleur.png");
	ListImages[3] = make_unique<QPixmap>();
	ListImages[3]->load("Textures\\Ennemis\\artilleur-d.png");
	ListImages[4] = make_unique<QPixmap>();
	ListImages[4]->load("Textures\\Ennemis\\divebomber.png");
	ListImages[5] = make_unique<QPixmap>();
	ListImages[5]->load("Textures\\Ennemis\\divebomber-d.png");
	ListImages[6] = make_unique<QPixmap>();
	ListImages[6]->load("Textures\\bullets\\basicbullet.png");
	ListImages[7] = make_unique<QPixmap>();
	ListImages[7]->load("Textures\\Ennemis\\aimbot.png");
	ListImages[8] = make_unique<QPixmap>();
	ListImages[8]->load("Textures\\Ennemis\\aimbot-d.png");
	ListImages[9] = make_unique<QPixmap>();
	ListImages[9]->load("Textures\\Ennemis\\big_mama.png");
	ListImages[10] = make_unique<QPixmap>();
	ListImages[10]->load("Textures\\Ennemis\\big_mama-d.png");
	ListImages[11] = make_unique<QPixmap>();
	ListImages[11]->load("Textures\\Ennemis\\boss1_main.png");
	ListImages[12] = make_unique<QPixmap>();
	ListImages[12]->load("Textures\\Ennemis\\boss1_main-d.png");
	ListImages[13] = make_unique<QPixmap>();
	ListImages[13]->load("Textures\\Ennemis\\boss1_side.png");
	ListImages[14] = make_unique<QPixmap>();
	ListImages[14]->load("Textures\\Ennemis\\boss1_side-d.png");
	ListImages[15] = make_unique<QPixmap>();
	ListImages[15]->load("Textures\\Ennemis\\tank.png");
	ListImages[16] = make_unique<QPixmap>();
	ListImages[16]->load("Textures\\Ennemis\\tank-d.png");
	ListImages[17] = make_unique<QPixmap>();
	ListImages[17]->load("Textures\\bullets\\homing.png");
	ListImages[18] = make_unique<QPixmap>();
	ListImages[18]->load("Textures\\bullets\\homing-d.png");
	ListImages[19] = make_unique<QPixmap>();
	ListImages[19]->load("Textures\\bullets\\laser.png");
	ListImages[20] = make_unique<QPixmap>();
	ListImages[20]->load("Textures\\bullets\\laser2.png");
	ListImages[21] = make_unique<QPixmap>();
	ListImages[21]->load("Textures\\Ennemis\\big_mama.png");
	ListImages[22] = make_unique<QPixmap>();
	ListImages[22]->load("Textures\\Ennemis\\big_mama-d.png");
	ListImages[23] = make_unique<QPixmap>();
	ListImages[23]->load("Textures\\Pup\\life.png");

	ListImages[24] = make_unique<QPixmap>();
	ListImages[24]->load("Textures\\Numbers\\0.png");
	ListImages[25] = make_unique<QPixmap>();
	ListImages[25]->load("Textures\\Numbers\\1.png");
	ListImages[26] = make_unique<QPixmap>();
	ListImages[26]->load("Textures\\Numbers\\2.png");
	ListImages[27] = make_unique<QPixmap>();
	ListImages[27]->load("Textures\\Numbers\\3.png");
	ListImages[28] = make_unique<QPixmap>();
	ListImages[28]->load("Textures\\Numbers\\4.png");
	ListImages[29] = make_unique<QPixmap>();
	ListImages[29]->load("Textures\\Numbers\\5.png");
	ListImages[30] = make_unique<QPixmap>();
	ListImages[30]->load("Textures\\Numbers\\6.png");
	ListImages[31] = make_unique<QPixmap>();
	ListImages[31]->load("Textures\\Numbers\\7.png");
	ListImages[32] = make_unique<QPixmap>();
	ListImages[32]->load("Textures\\Numbers\\8.png");
	ListImages[33] = make_unique<QPixmap>();
	ListImages[33]->load("Textures\\Numbers\\9.png");

	ListImages[34] = make_unique<QPixmap>();
	ListImages[34]->load("Textures\\Ennemis\\orbiter.png");
	ListImages[35] = make_unique<QPixmap>();
	ListImages[35]->load("Textures\\Ennemis\\orbiter-d.png");
	ListImages[36] = make_unique<QPixmap>();
	ListImages[36]->load("Textures\\Pup\\addLife.png");
	ListImages[37] = make_unique<QPixmap>();
	ListImages[37]->load("Textures\\Pup\\addAmo.png");
	ListImages[38] = make_unique<QPixmap>();
	ListImages[38]->load("Textures\\Sprites\\barrel_roll.png");
	ListImages[39] = make_unique<QPixmap>();
	ListImages[39]->load("Textures\\Sprites\\barrel_roll-d.png");

	ListImages[40] = make_unique<QPixmap>();
	ListImages[40]->load("Textures\\bullets\\canon.png");
	ListImages[41] = make_unique<QPixmap>();
	ListImages[41]->load("Textures\\Ennemis\\sideBomber.png");
	ListImages[42] = make_unique<QPixmap>();
	ListImages[42]->load("Textures\\Ennemis\\sideBomber-d.png");
	ListImages[43] = make_unique<QPixmap>();
	ListImages[43]->load("Textures\\Sprites\\boss2.png");
	ListImages[44] = make_unique<QPixmap>();
	ListImages[44]->load("Textures\\Sprites\\boss2-d.png");
	ListImages[46] = make_unique<QPixmap>();
	ListImages[46]->load("Textures\\Ennemis\\boss3_main.png");
	ListImages[47] = make_unique<QPixmap>();
	ListImages[47]->load("Textures\\Ennemis\\boss3_main-d.png");
	ListImages[48] = make_unique<QPixmap>();
	ListImages[48]->load("Textures\\Ennemis\\boss3_side.png");
	ListImages[49] = make_unique<QPixmap>();
	ListImages[49]->load("Textures\\Ennemis\\boss3_side-d.png");
	ListImages[50] = make_unique<QPixmap>();
	ListImages[50]->load("Textures\\Ennemis\\exploder.png");
	ListImages[51] = make_unique<QPixmap>();
	ListImages[51]->load("Textures\\Ennemis\\exploder-d.png");
	ListImages[52] = make_unique<QPixmap>();
	ListImages[52]->load("Textures\\Sprites\\turret.png");
	ListImages[53] = make_unique<QPixmap>();
	ListImages[53]->load("Textures\\Sprites\\turret-d.png");
	ListImages[54] = make_unique<QPixmap>();
	ListImages[54]->load("Textures\\Ennemis\\exploder.png");
	ListImages[55] = make_unique<QPixmap>();
	ListImages[55]->load("Textures\\Ennemis\\exploder-d.png");
	ListImages[56] = make_unique<QPixmap>();
	ListImages[56]->load("Textures\\Ennemis\\tankR.png");
	ListImages[57] = make_unique<QPixmap>();
	ListImages[57]->load("Textures\\Ennemis\\tankR-d.png");

	ListImages[58] = make_unique<QPixmap>();
	ListImages[58]->load("Textures\\Numbers\\0-R.png");
	ListImages[59] = make_unique<QPixmap>();
	ListImages[59]->load("Textures\\Numbers\\1-R.png");
	ListImages[60] = make_unique<QPixmap>();
	ListImages[60]->load("Textures\\Numbers\\2-R.png");
	ListImages[61] = make_unique<QPixmap>();
	ListImages[61]->load("Textures\\Numbers\\3-R.png");
	ListImages[62] = make_unique<QPixmap>();
	ListImages[62]->load("Textures\\Numbers\\4-R.png");
	ListImages[63] = make_unique<QPixmap>();
	ListImages[63]->load("Textures\\Numbers\\5-R.png");
	ListImages[64] = make_unique<QPixmap>();
	ListImages[64]->load("Textures\\Numbers\\6-R.png");
	ListImages[65] = make_unique<QPixmap>();
	ListImages[65]->load("Textures\\Numbers\\7-R.png");
	ListImages[66] = make_unique<QPixmap>();
	ListImages[66]->load("Textures\\Numbers\\8-R.png");
	ListImages[67] = make_unique<QPixmap>();
	ListImages[67]->load("Textures\\Numbers\\9-R.png");
	ListImages[68] = make_unique<QPixmap>();
	ListImages[68]->load("Textures\\Numbers\\x.png");

	ListImages[69] = make_unique<QPixmap>();
	ListImages[69]->load("Textures\\Sprites\\barrel_roll2.png");
	ListImages[70] = make_unique<QPixmap>();
	ListImages[70]->load("Textures\\Sprites\\barrel_roll2-d.png");




}
///////////////////////////////

extern std::unique_ptr<Interface> jeux = nullptr;

///// EXECUTIONS DE JEU ////////////
bool firstlaunchSolo = true;
bool firstlaunchCoop = true;
void firststartSolo() {
	if (firstlaunchSolo == true && firstlaunchCoop == true) {
		loadimages();
		firstlaunchSolo = false; // Set first to false after the first run
		jeux = std::make_unique<Interface>();// Create an instance of a concrete implementation
	}
	else {
		if (jeux) {
			jeux->executionJeu(0); // Call executionJeu if the object exists
		}
	}
	firstlaunchSolo = false;
}






void firststartCoop() {
	if (firstlaunchSolo == true && firstlaunchCoop == true) {
		loadimages();
		firstlaunchCoop = false; // Set first to false after the first run
		jeux = std::make_unique<Interface>();// Create an instance of a concrete implementation
		view->setScene(GameScene);
	}

	else {
		if (jeux) {
			jeux->executionJeu(1); // Call executionJeu if the object exists
		}
	}
	firstlaunchCoop = false;
}









///////////////////////////////////





















GererMenu::GererMenu(QObject* parent)
	: QGraphicsScene(parent)
{
	this->setSceneRect(0, 0, 1920, 1080);

	gameTitle = new QGraphicsTextItem("FLIGHT FRENZY");
	gameTitle->setFont(QFont("Arial", 24, QFont::Bold));
	gameTitle->setDefaultTextColor(Qt::black);
	gameTitle->setPos((1920 - gameTitle->boundingRect().width()) / 2, 200);
	addItem(gameTitle);

	this->setBackgroundBrush(QBrush(QColor(135, 206, 250)));

	QPushButton* jouerBouton = new QPushButton("JOUER");
	jouerBouton->setGeometry(QRect(720, 350, 480, 47));
	proxyJouer = addWidget(jouerBouton);

	QPushButton* audioBouton = new QPushButton("AUDIO");
	audioBouton->setGeometry(QRect(720, 450, 480, 47));
	proxyAudio = addWidget(audioBouton);

	QPushButton* classementBouton = new QPushButton("CLASSEMENT");
	classementBouton->setGeometry(QRect(720, 550, 480, 47));
	proxyClassement = addWidget(classementBouton);

	QPushButton* quitterBouton = new QPushButton("QUITTER");
	quitterBouton->setGeometry(QRect(720, 650, 480, 47));
	proxyQuitter = addWidget(quitterBouton);
	connect(jouerBouton, &QPushButton::clicked, this, &GererMenu::jouerPeser);
	connect(audioBouton, &QPushButton::clicked, this, &GererMenu::audioPeser);
	connect(classementBouton, &QPushButton::clicked, this, &GererMenu::classementPeser);
	connect(quitterBouton, &QPushButton::clicked, this, &GererMenu::quitterPeser);
}


GererMenu::~GererMenu()
{
}

void GererMenu::setFondEcran()
{
	QPixmap fondEcran("C:\\Users\\User\\OneDrive - USherbrooke\\Images\\Saved Pictures\\Air.png");
	fondEcran.scaled(1200, 700);

	QPalette couleurFond;
	couleurFond.setBrush(QPalette::Window, fondEcran);
	this->setPalette(couleurFond);
}

void GererMenu::jouerPeser()
{
	ChoixMode* mode = new ChoixMode(nullptr);
	view->setScene(mode);

}

void GererMenu::audioPeser()
{
	Audio* audio = new Audio(nullptr);
	view->setScene(audio);

}

void GererMenu::classementPeser()
{
	Classement* classement = new Classement;
	view->setScene(classement);
}

void GererMenu::quitterPeser()
{
	Quitter* quitter = new Quitter(nullptr);
	view->setScene(quitter);

}


ChoixMode::ChoixMode(QObject* parent) : QGraphicsScene(parent)
{
	setFondEcran();


	soloBouton = new QPushButton("SOLO");
	soloBouton->setGeometry(QRect(550, 200, 100, 50));
	proxySolo = addWidget(soloBouton);

	coopBouton = new QPushButton("COOP");
	coopBouton->setGeometry(QRect(550, 300, 100, 50));
	proxyCoop = addWidget(coopBouton);

	revenirBouton = new QPushButton("REVENIR");
	revenirBouton->setGeometry(QRect(550, 400, 100, 50));
	proxyRevenir = addWidget(revenirBouton);

	connect(soloBouton, &QPushButton::clicked, this, &ChoixMode::soloPeser);
	connect(coopBouton, &QPushButton::clicked, this, &ChoixMode::coopPeser);
	connect(revenirBouton, &QPushButton::clicked, this, &ChoixMode::revenirPeser);

}

ChoixMode::~ChoixMode()
{
}

void ChoixMode::setFondEcran()
{
	QPixmap fondEcran("C:\\Users\\User\\OneDrive - USherbrooke\\Images\\Saved Pictures\\Air.png");
	fondEcran.scaled(1200, 700);

	QPalette couleurFond;
	couleurFond.setBrush(QPalette::Window, fondEcran);
	this->setPalette(couleurFond);
}

void ChoixMode::soloPeser()
{
	Utilisateur* utilisateur = new Utilisateur(nullptr);
	view->setScene(utilisateur);

}

void ChoixMode::coopPeser()
{
	Equipe* equipe = new Equipe(nullptr);
	view->setScene(equipe);
}

void ChoixMode::revenirPeser()
{
	GererMenu* menu = new GererMenu(nullptr);
	view->setScene(menu);
}



Audio::Audio(QObject* parent) : QGraphicsScene(parent)
{

	QFont font("Roboto", 14, QFont::Bold);

	sfxTitle = new QLabel("SFX");
	sfxTitle->setGeometry(QRect(550, 125, 100, 50));
	proxySfxTitle = addWidget(sfxTitle);

	sfxValue = new QLabel(QString::number(sfx.getvolume()));
	sfxValue->setGeometry(QRect(575, 185, 50, 50));
	proxySfxValue = addWidget(sfxValue);

	musiqueTitle = new QLabel("MUSIQUE");
	musiqueTitle->setGeometry(QRect(550, 325, 100, 50));
	proxyMusiqueTitle = addWidget(musiqueTitle);

	musiqueValue = new QLabel(QString::number(music.getvolume()));
	musiqueValue->setGeometry(QRect(575, 385, 50, 50));
	proxyMusiqueValue = addWidget(musiqueValue);

	sfxBoutonUp = new QPushButton("+");
	sfxBoutonUp->setGeometry(QRect(675, 200, 50, 20));
	proxySfxBoutonUp = addWidget(sfxBoutonUp);

	sfxBoutonDown = new QPushButton("-");
	sfxBoutonDown->setGeometry(QRect(475, 200, 50, 20));
	proxySfxBoutonDown = addWidget(sfxBoutonDown);

	musiqueBoutonUp = new QPushButton("+");
	musiqueBoutonUp->setGeometry(QRect(675, 400, 50, 20));
	proxyMusiqueBoutonUp = addWidget(musiqueBoutonUp);

	musiqueBoutonDown = new QPushButton("-");
	musiqueBoutonDown->setGeometry(QRect(475, 400, 50, 20));
	proxyMusiqueBoutonDown = addWidget(musiqueBoutonDown);

	revenirBouton = new QPushButton("REVENIR");
	revenirBouton->setGeometry(QRect(550, 575, 100, 50));
	proxyRevenirBouton = addWidget(revenirBouton);

	connect(sfxBoutonUp, &QPushButton::clicked, this, &Audio::sfxPlus);
	connect(sfxBoutonDown, &QPushButton::clicked, this, &Audio::sfxMoins);
	connect(musiqueBoutonUp, &QPushButton::clicked, this, &Audio::musiquePlus);
	connect(musiqueBoutonDown, &QPushButton::clicked, this, &Audio::musiqueMoins);
	revenirPeser();

}


Audio::~Audio()
{
}

void Audio::setFondEcran()
{
	QPixmap fondEcran("C:\\Users\\User\\OneDrive - USherbrooke\\Images\\Saved Pictures\\Air.png");
	fondEcran.scaled(1200, 700);

	QPalette couleurFond;
	couleurFond.setBrush(QPalette::Window, fondEcran);
	this->setPalette(couleurFond);
}

void Audio::sfxPlus()
{
	float volume_SFX;
	volume_SFX = min(sfx.getvolume() + 5, 100.0f);
	//set le volume de toutes les SFX
	setallSFXVolume(volume_SFX);
	sfx.playSFX("pling.wav");
	sfxValue->setText(QString::number(sfx.getvolume()));
}

void Audio::sfxMoins()
{
	float volume_SFX;
	volume_SFX = max(sfx.getvolume() - 5, 0.0f);
	//set le volume de toutes les SFX
	setallSFXVolume(volume_SFX);
	sfx.playSFX("pling.wav");
	sfxValue->setText(QString::number(sfx.getvolume()));
}

void Audio::musiquePlus()
{
	float volume_musique;
	volume_musique = min(music.getvolume() + 5, 100.0f);
	music.setVolume(volume_musique);
	musiqueValue->setText(QString::number(music.getvolume()));
}

void Audio::musiqueMoins()
{
	float volume_musique;
	volume_musique = max(music.getvolume() - 5, 0.0f);
	music.setVolume(volume_musique);
	musiqueValue->setText(QString::number(music.getvolume()));
}

void Audio::revenirPeser()
{

	connect(revenirBouton, &QPushButton::clicked, this, &Audio::revenir);
}

void Audio::revenir()
{
	GererMenu* menu = new GererMenu(nullptr);
	savesettings();
	view->setScene(menu);
}

Quitter::Quitter(QObject* parent) : QGraphicsScene(parent)
{

	//Boutons Choix de Mode
	QFont font("Roboto", 18, QFont::Bold);
	confirmationQuitter = new QLabel("ETES-VOUS CERTAIN DE VOULOIR QUITTER ?");
	confirmationQuitter->setGeometry(QRect(250, 50, 700, 100));
	proxyConfirmationQuitter = addWidget(confirmationQuitter);

	ouiBouton = new QPushButton("OUI");
	ouiBouton->setGeometry(QRect(550, 300, 100, 50));
	proxyOuiBouton = addWidget(ouiBouton);

	nonBouton = new QPushButton("NON");
	nonBouton->setGeometry(QRect(550, 400, 100, 50));
	proxyNonBouton = addWidget(nonBouton);


	//Signales
	ouiPeser();
	nonPeser();
}
Quitter::~Quitter()
{
}
void Quitter::ouiPeser()
{
	connect(ouiBouton, &QPushButton::clicked, this, &Quitter::quitter);
}

void Quitter::nonPeser()
{
	connect(nonBouton, &QPushButton::clicked, this, &Quitter::revenir);
}

void Quitter::quitter()
{
	view->hide();
	view->viewport()->deleteLater();
	QApplication::quit();
}

void Quitter::revenir()
{
	GererMenu* menu = new GererMenu(nullptr);
	view->setScene(menu);

}


Classement::Classement(QObject* parent) : QGraphicsScene(parent)
{

	QFont font("Courier", 12, QFont::Bold);

	revenirBouton = new QPushButton("REVENIR");
	revenirBouton->setGeometry(QRect(550, 575, 100, 50));
	proxyRevenirBouton = addWidget(revenirBouton);

	classementSolo = new QTextEdit;
	classementSolo->setGeometry(QRect(150, 100, 330, 400));
	classementSolo->setFont(font);
	classementSolo->setReadOnly(true);
	proxyClassementSolo = addWidget(classementSolo);
	montrer_classement_solo();

	classementCoop = new QTextEdit;
	classementCoop->setGeometry(QRect(700, 100, 330, 400));
	classementCoop->setFont(font);
	classementCoop->setReadOnly(true);
	proxyClassementCoop = addWidget(classementCoop);
	montrer_classement_coop();


	//Signales
	revenirPeser();
}


Classement::~Classement()
{
}

void Classement::setFondEcran()
{
	QPixmap fondEcran("C:\\Users\\User\\OneDrive - USherbrooke\\Images\\Saved Pictures\\Air.png");
	fondEcran.scaled(1200, 700);

	QPalette couleurFond;
	couleurFond.setBrush(QPalette::Window, fondEcran);
	this->setPalette(couleurFond);
}

void Classement::revenirPeser()
{
	connect(revenirBouton, &QPushButton::clicked, this, &Classement::revenir);
}

void Classement::revenir()
{
	GererMenu* menu = new GererMenu(nullptr);
	view->setScene(menu);
}

void Classement::montrer_classement_solo()
{
	ifstream scores("ScoresJoueurs.txt");
	string nom_joueur;
	int score_joueur;
	int position = 1;
	int top = 0;

	if (scores.is_open())
	{
		while (scores >> nom_joueur >> score_joueur) {
			ScoreSolo.push_back({ position++, nom_joueur, score_joueur });
		}
		scores.close();
	}

	else
	{
		qDebug() << "Failed to open ScoresJoueurs.txt";
		return;
	}

	ligneClassementSolo = "\tCLASSEMENT SOLO\n";
	ligneClassementSolo += "=================================\n\n\n";
	ligneClassementSolo += "TOP |      NOM     | SCORE\n";
	ligneClassementSolo += "---------------------------------\n";

	for (const auto& scores_solo : ScoreSolo) {
		if (top < 10)
		{
			ligneClassementSolo += QString::number(scores_solo.position).leftJustified(3, ' ') + " | ";
			ligneClassementSolo += QString::fromStdString(scores_solo.nom).leftJustified(12, ' ') + " | ";
			ligneClassementSolo += QString::number(scores_solo.score).rightJustified(5, ' ') + "\n";
		}
		top++;
	}

	ligneClassementSolo += "---------------------------------\n";
	classementSolo->setText(ligneClassementSolo);

	ScoreSolo.clear();
}

void Classement::montrer_classement_coop()
{
	ifstream scores("ScoresEquipes.txt");
	string nom_equipe;
	int score_equipe;
	int position = 1;
	int top = 0;

	if (scores.is_open())
	{
		while (scores >> nom_equipe >> score_equipe) {
			ScoreCoop.push_back({ position++, nom_equipe, score_equipe });
		}
		scores.close();
	}

	else
	{
		qDebug() << "Failed to open ScoresEquipes.txt";
		return;
	}

	ligneClassementCoop = "\tCLASSEMENT COOP\n";
	ligneClassementCoop += "=================================\n\n\n";
	ligneClassementCoop += "TOP |    EQUIPE    | SCORE\n";
	ligneClassementCoop += "---------------------------------\n";

	for (const auto& scores_coop : ScoreCoop) {
		if (top < 10)
		{
			ligneClassementCoop += QString::number(scores_coop.position).leftJustified(3, ' ') + " | ";
			ligneClassementCoop += QString::fromStdString(scores_coop.equipe).leftJustified(12, ' ') + " | ";
			ligneClassementCoop += QString::number(scores_coop.score).rightJustified(5, ' ') + "\n";
		}
		top++;
	}

	ligneClassementCoop += "---------------------------------\n";
	classementCoop->setText(ligneClassementCoop);

	ScoreCoop.clear();
}

void Classement::ajouter_score_solo() {

	ifstream scoresFileIn("ScoresJoueurs.txt");
	string nom_joueur;
	int joueur_score;
	vector<classement_solo> liste_scores;
	//Utilisateur utilisateur;
	Interface jeu;

	while (scoresFileIn >> nom_joueur >> joueur_score) {
		liste_scores.push_back({ 0, nom_joueur, joueur_score });
	}
	scoresFileIn.close();

	//string nom;// = utilisateur.get_nom();
	//int score = jeu.get_score_solo();
	//liste_scores.push_back({ 0, nom, score });

	sort(liste_scores.begin(), liste_scores.end(), [](const classement_solo& a, const classement_solo& b) {
		return a.score > b.score;
	});

	for (size_t i = 0; i < liste_scores.size(); ++i) {
		liste_scores[i].position = i + 1;
	}

	ofstream scoresFileOut("ScoresJoueurs.txt");
	for (auto& nouveau_solo : liste_scores) {
		scoresFileOut << nouveau_solo.nom << " " << nouveau_solo.score << endl;
	}

	scoresFileOut.close();

}

void Classement::ajouter_score_coop() {

	ifstream scoresFileIn("ScoresEquipes.txt");
	string nom_equipe;
	int equipe_score;
	vector<classement_coop> liste_scores;


	while (scoresFileIn >> nom_equipe >> equipe_score) {
		liste_scores.push_back({ 0, nom_equipe, equipe_score });
	}
	scoresFileIn.close();

	//string nom = equipe.get_equipe();
	//int score = jeux->get_score_coop();
	//liste_scores.push_back({ 0, nom, score });

	sort(liste_scores.begin(), liste_scores.end(), [](const classement_coop& a, const classement_coop& b) {
		return a.score > b.score;
	});

	for (size_t i = 0; i < liste_scores.size(); ++i) {
		liste_scores[i].position = i + 1;
	}

	ofstream scoresFileOut("ScoresEquipes.txt");
	for (auto& nouveau_coop : liste_scores) {
		scoresFileOut << nouveau_coop.equipe << " " << nouveau_coop.score << endl;
	}

	scoresFileOut.close();
}


JouerSolo::JouerSolo(QObject* parent) : QGraphicsScene(parent)
{
	QFont font("Roboto", 18, QFont::Bold);

	confirmationJouer = new QLabel("ETES-VOUS CERTAIN DE VOULOIR COMMENCER ?");
	confirmationJouer->setGeometry(QRect(250, 50, 700, 100));
	proxyConfirmationJouer = addWidget(confirmationJouer);

	ouiBouton = new QPushButton("OUI");
	ouiBouton->setGeometry(QRect(550, 300, 100, 50));
	proxyOuiBouton = addWidget(ouiBouton);

	nonBouton = new QPushButton("NON");
	nonBouton->setGeometry(QRect(550, 400, 100, 50));
	proxyNonBouton = addWidget(nonBouton);

	//Signales
	ouiPeser();
	nonPeser();
}

JouerSolo::~JouerSolo()
{
}

void JouerSolo::setFondEcran()
{

}

void JouerSolo::ouiPeser()
{
	connect(ouiBouton, &QPushButton::clicked, this, &JouerSolo::commencerSolo);
}

void JouerSolo::nonPeser()
{
	connect(nonBouton, &QPushButton::clicked, this, &JouerSolo::revenir);
}

void JouerSolo::commencerSolo()
{
	//execution du jeu solo
	view->setScene(GameScene);
	if (firstlaunchSolo)
	{
		QObject::connect(&Solotimer, &QTimer::timeout, [&]() { firststartSolo(); });
	}
	if (!firstlaunchCoop || !firstlaunchSolo)
	{
		music.playMusic("Ocean.wav", 0, 117000);
	}
	Solotimer.start(16);
	//Classement classement;
	//classement.ajouter_score_solo();
}

void JouerSolo::revenir()
{
	ChoixMode* mode = new ChoixMode(nullptr);
	view->setScene(mode);

}


Utilisateur::Utilisateur(QObject* parent) : QGraphicsScene(parent)
{

	//Texte Nom
	QFont font("Roboto", 18, QFont::Bold);

	entrerNom = new QLabel("ENTREZ VOTRE NOM DE JOUEUR:");
	entrerNom->setGeometry(QRect(400, 150, 400, 100));
	proxyEntrerNom = addWidget(entrerNom);

	nomSolo = new QLineEdit;
	nomSolo->setGeometry(QRect(450, 250, 300, 50));
	proxyNomSolo = addWidget(nomSolo);

	valider = new QPushButton("VALIDER");
	valider->setGeometry(QRect(850, 250, 100, 50));
	proxyValider = addWidget(valider);

	connect(valider, &QPushButton::clicked, this, &Utilisateur::suivant);


}

Utilisateur::~Utilisateur()
{
}

void Utilisateur::setFondEcran()
{
}

void Utilisateur::suivant()
{
	nomJoueur = nomSolo->text();
	JouerSolo* jouer = new JouerSolo(nullptr);
	view->setScene(jouer);
	qDebug() << nomJoueur;
}

string Utilisateur::get_nom()
{
	return nomJoueur.toStdString();
}

JouerCoop::JouerCoop(QObject* parent) : QGraphicsScene(parent)
{


	//Texte Jouer
	QFont font("Roboto", 18, QFont::Bold);

	confirmationJouer = new QLabel("ETES-VOUS CERTAIN DE VOULOIR COMMENCER ?");
	confirmationJouer->setGeometry(QRect(250, 50, 700, 100));
	proxyConfirmationJouer = addWidget(confirmationJouer);

	ouiBouton = new QPushButton("OUI");
	ouiBouton->setGeometry(QRect(550, 300, 100, 50));
	proxyOuiBouton = addWidget(ouiBouton);

	nonBouton = new QPushButton("NON");
	nonBouton->setGeometry(QRect(550, 400, 100, 50));
	proxyNonBouton = addWidget(nonBouton);



	//Signales
	ouiPeser(); //to fix
	nonPeser();
}

JouerCoop::~JouerCoop()
{
}

void JouerCoop::setFondEcran()
{
}

void JouerCoop::ouiPeser()
{
	connect(ouiBouton, &QPushButton::clicked, this, &JouerCoop::commencerCoop);
}

void JouerCoop::nonPeser()
{
	connect(nonBouton, &QPushButton::clicked, this, &JouerCoop::revenir);
}

void JouerCoop::commencerCoop()
{
	//execution du jeu coop
	view->setScene(GameScene);
	if (firstlaunchCoop)
	{
		QObject::connect(&Cooptimer, &QTimer::timeout, [&]() { firststartCoop(); });
	}
	if (!firstlaunchCoop || !firstlaunchSolo)
	{
		music.playMusic("Ocean.wav", 0, 117000);
	}
	Cooptimer.start(16);
	//Classement classement;
	//classement.ajouter_score_coop();
}

void JouerCoop::revenir()
{
	ChoixMode* mode = new ChoixMode(nullptr);
	view->setScene(mode);

}

Equipe::Equipe(QObject* parent) : QGraphicsScene(parent)
{
	//Texte Equipe
	QFont font("Roboto", 18, QFont::Bold);

	entrerEquipe = new QLabel("ENTREZ VOTRE NOM D'EQUIPE:");
	entrerEquipe->setGeometry(QRect(400, 150, 400, 100));
	proxyEntrerEquipe = addWidget(entrerEquipe);

	nomCoop = new QLineEdit;
	nomCoop->setGeometry(QRect(450, 250, 300, 50));
	proxyNomCoop = addWidget(nomCoop);

	valider = new QPushButton("VALIDER");
	valider->setGeometry(QRect(850, 250, 100, 50));
	proxyValider = addWidget(valider);

	connect(valider, &QPushButton::clicked, this, &Equipe::suivant);

}

Equipe::~Equipe()
{
}

void Equipe::setFondEcran()
{
	QPixmap fondEcran("C:\\Users\\User\\OneDrive - USherbrooke\\Images\\Saved Pictures\\Air.png");
	fondEcran.scaled(1200, 700);

	QPalette couleurFond;
	couleurFond.setBrush(QPalette::Window, fondEcran);
	this->setPalette(couleurFond);
}

void Equipe::suivant()
{
	nomEquipe = nomCoop->text();
	JouerCoop* jouer = new JouerCoop(nullptr);
	view->setScene(jouer);
	qDebug() << nomEquipe;
}

string Equipe::get_equipe()
{
	return nomEquipe.toStdString();
}