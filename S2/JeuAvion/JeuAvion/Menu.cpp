/*#include "Menu.h"

Gerer_Menu menu_principal;
Jouer jouer;
ChoixMode mode;
Audio audio;
Classement classement;
Quitter quitter;
double MainMenuOn = false;

void Gerer_Menu::afficher(int choix_option) {
	const int taille_menu = 4;
	string menu[taille_menu] = { "JOUER", "AUDIO", "CLASSEMENT", "QUITTER" };

	system("cls");
	cout << "===== MENU =====" << endl;

	for (int i = 0; i < taille_menu; i++) {
		if (i == choix_option) {
			cout << "* ";
		}
		cout << menu[i] << endl;
	}
	cout << "================" << endl;
}

void Gerer_Menu::peser() {
	int choix_option = 0;
	char touche_peser;
	if(MainMenuOn== false)

	{
		music.stopMusic();
		music.playMusic("MainMenu.wav", 65548, 63989);
		MainMenuOn = true;
	}
	afficher(choix_option);
	Sleep(100);

	while (true) {
		//afficher(choix_option);
		//touche_peser = _getch();
		if (MainMenuOn == false)

		{
			music.stopMusic();
			music.playMusic("MainMenu.wav", 65548, 63989);
			MainMenuOn = true;
			afficher(choix_option);
		}
		if (GetAsyncKeyState('W') < 0)
		{
			if (choix_option == 0)
			{
				choix_option = 0;
			}
			else
			{
				choix_option = choix_option - 1;
				sfx.playSFX("pling.wav");
			}
			afficher(choix_option);
			//Sleep(25);
		}
		else if (GetAsyncKeyState('S') < 0)
		{
			if (choix_option == 3)
				choix_option = 3;
			else
			{
				sfx.playSFX("pling.wav");
				choix_option = choix_option + 1;
			}
			afficher(choix_option);
			//Sleep(25);
		}
		else if (GetAsyncKeyState('\r') < 0)
		{
			switch (choix_option) {
			case 0:
				mode.peser();
				sfx.playSFX("Select.wav");
				break;
			case 1:
				sfx.playSFX("Select.wav");
				audio.peser();
				break;
			case 2: 
				exit(0);
				break;
			case 3:
				quitter.peser();
				break;
			}

		}
		Sleep(75);
	}
}

void Jouer::afficher(int choix_option) {
	const int taille_menu_jouer = 2;
	string menu[taille_menu_jouer] = { "OUI", "NON" };
	system("cls");

	cout << "===== ETES VOUS SUR DE VOULOIR COMMENCER ? =====" << endl;

	for (int i = 0; i < taille_menu_jouer; i++) {
		if (i == choix_option) {
			cout << "* ";
		}
		cout << menu[i] << endl;
	}
	cout << "================================================" << endl;
}

void Jouer::peser() {
	int choix_option = 0;
	char touche_peser;

	afficher(choix_option);

	Sleep(100);	

	while (true) {

		if (GetAsyncKeyState('W') < 0)
		{
			if (choix_option == 0) {
				choix_option = 0;
			}
			else {
				sfx.playSFX("pling.wav");
				choix_option = choix_option - 1;
			}
			afficher(choix_option);
		}
		else if (GetAsyncKeyState('S') < 0)
		{
			if (choix_option == 1)
				choix_option = 1;
			else
			{
				sfx.playSFX("pling.wav");
				choix_option = choix_option + 1;

			}
			afficher(choix_option);
		}
		else if (GetAsyncKeyState('\r') < 0)
		{
			switch (choix_option) 
			{
			case 0:
				MainMenuOn = false;
				sfx.playSFX("Select.wav");
				//music2.setVolume(500);
				//music2.playMusic("OceanWorld.wav");
				jeux.executionJeu(1);
				return;
			case 1:
				menu_principal.peser();
				return;
			}
		}
		Sleep(75);
	}
}

void ChoixMode::afficher(int choix_option)
{
	const int taille_menu = 2;
	string menu[taille_menu] = { "SOLO", "COOP"};

	system("cls");
	cout << "===== CHOIX DE MODE =====" << endl;

	for (int i = 0; i < taille_menu; i++) {
		if (i == choix_option) {
			cout << "* ";
		}
		cout << menu[i] << endl;
	}
	cout << "================" << endl;

}

void ChoixMode::peser()
{
	int choix_option = 0;
	char touche_peser;
	afficher(choix_option);

	Sleep(100);

	while (true) {

		if (GetAsyncKeyState('W') < 0)
		{
			if (choix_option == 0) {
				choix_option = 0;
			}
			else {
				sfx.playSFX("pling.wav");
				choix_option = choix_option - 1;
			}
			afficher(choix_option);
		}
		else if (GetAsyncKeyState('S') < 0)
		{
			if (choix_option == 1)
				choix_option = 1;
			else
			{
				sfx.playSFX("pling.wav");
				choix_option = choix_option + 1;

			}
			afficher(choix_option);
		}
		else if (GetAsyncKeyState('\r') < 0)
		{
			switch (choix_option)
			{
			case 0:
				MainMenuOn = false;
				sfx.playSFX("Select.wav");
				jeux.executionJeu(0);
				return;
			case 1:
				MainMenuOn = false;
				sfx.playSFX("Select.wav");
				jeux.executionJeu(1);
				return;
			}
		}
		Sleep(75);
	}
}


void Quitter::afficher(int choix_option) {
	const int taille_menu_quitter = 2;
	string menu[taille_menu_quitter] = { "OUI", "NON" };
	system("cls");

	cout << "===== ETES VOUS SUR DE VOULOIR QUITTER ? =====" << endl;

	for (int i = 0; i < taille_menu_quitter; i++) {
		if (i == choix_option) {
			cout << "* ";
		}
		cout << menu[i] << endl;
	}
	cout << "================================================" << endl;
}

void Quitter::peser() {
	int choix_option = 0;
	char touche_peser;

	afficher(choix_option);
	Sleep(200);

	while (true) {
		
		if (GetAsyncKeyState('W') < 0)
		{
			if (choix_option == 0)
				choix_option = 0;
			else
			{
				choix_option = choix_option - 1;
				sfx.playSFX("pling.wav");
			}
			afficher(choix_option);
		}
		else if (GetAsyncKeyState('S') < 0)
		{
			if (choix_option == 1)
				choix_option = 1;
			else
			{
				choix_option = choix_option + 1;
				sfx.playSFX("pling.wav");
			}
			afficher(choix_option);
		}
		else if (GetAsyncKeyState('\r') < 0)
		{
			switch (choix_option) {
			case 0:
				exit(0);
			case 1:
				menu_principal.peser();
				return;
			}
		}
		Sleep(75);
	}
}

void Audio::afficher(int choix_option) {
	const int taille_menu_audio = 3;
	string menu[taille_menu_audio] = { "MUSIQUE: ","SFX: ", "RETOUR" };
	system("cls");

	cout << "===== AUDIO =====" << endl;

	for (int i = 0; i < taille_menu_audio; i++) {
		if (i == choix_option) {
			cout << "* ";
		}
		if (i == 0)
		{
			cout << menu[i] << music.getvolume() << endl;
		}
		if (i == 1)
		{
			cout << menu[i] << sfx.getvolume() << endl;
		}
		if (i == 2)
		{
			cout << menu[i] << endl;
		}
	}
		cout << "=================" << endl;
}


void Audio::peser() {
	int choix_option = 0;
	char touche_peser;
	afficher(choix_option);
	Sleep(200);
	while (true) 
	{
		if (GetAsyncKeyState('W') < 0)
		{
			if (choix_option == 0)
				choix_option = 0;
			else
			{
				choix_option = choix_option - 1;
				sfx.playSFX("pling.wav");
			}
			afficher(choix_option);
		}
		else if (GetAsyncKeyState('S') < 0)
		{
			if (choix_option == 2)
				choix_option = 2;
			else
			{
				choix_option = choix_option + 1;
				sfx.playSFX("pling.wav");
			}
			afficher(choix_option);
		}
		if (GetAsyncKeyState('A') < 0)
		{
			if(choix_option == 0){
			if (music.getvolume() == 0)
				continue;
			else
				diminuer_volumemusique();

			afficher(choix_option);
			}

			if (choix_option == 1) {
				if (sfx.getvolume() == 0)
					continue;
				else
					diminuer_volumeSFX();

				afficher(choix_option);
			}

		}
		else if (GetAsyncKeyState('D') < 0)
		{
			if(choix_option == 0)
			{
			if (music.getvolume() == 100)
				continue;
			else
				augmenter_volumemusique();

			afficher(choix_option);
			}
			if (choix_option == 1)
			{
				if (sfx.getvolume() == 100)
					continue;
				else
					augmenter_volumeSFX();

				afficher(choix_option);
			}

		}
		else if (GetAsyncKeyState('\r') < 0)
		{
			if (choix_option == 2)
			{
				savesettings();
				menu_principal.peser();
			}
		}
		Sleep(75);
		
	}
}

void Audio::augmenter_volumemusique() {
	float volume_musique;
	volume_musique = music.getvolume() + 5;
	music.setVolume(volume_musique);
}

void Audio::diminuer_volumemusique() {
	float volume_musique;
	volume_musique = music.getvolume() - 5;
	music.setVolume(volume_musique);
}

void Audio::augmenter_volumeSFX() {
	float volume_SFX;
	volume_SFX = sfx.getvolume() + 5;
//set le volume de toutes les SFX
	setallSFXVolume(volume_SFX);
	sfx.playSFX("pling.wav");
}

void Audio::diminuer_volumeSFX() {
	float volume_SFX;
	volume_SFX = sfx.getvolume() - 5;
	//set le volume de toutes les SFX
	setallSFXVolume(volume_SFX);
	sfx.playSFX("pling.wav");
}

void Classement::afficher(int choix_option) {
	//apres avoir stocker le nom utilisateur, stocker son score respectif et
	//faire un tableau des meilleurs scores
}

void Classement::peser() {

}

void Utilisateur::afficher(int choix_option) {
	//demander nom utilisateur apres avoir cliquer sur jouer
}

void Utilisateur::peser() {

}
*/