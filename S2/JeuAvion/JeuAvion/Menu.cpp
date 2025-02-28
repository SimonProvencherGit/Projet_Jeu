#include "Menu.h"

Gerer_Menu menu_principal;
Jouer jouer;
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
		music.playMusic("MainMenu.wav");
		MainMenuOn = true;
	}

	while (true) {
		afficher(choix_option);
		touche_peser = _getch();
		if (MainMenuOn == false)

		{
			music.stopMusic();
			music.playMusic("MainMenu.wav");
			MainMenuOn = true;
		}

		switch (touche_peser) {
		case 'w':
			if (choix_option == 0)
			{
				choix_option = 0;
			}

			else
			{
				choix_option = choix_option - 1;
				sfx.playSFX("pling.wav");
			}
			break;

		case 's':
			if (choix_option == 3)
				choix_option = 3;
			else
			{
				sfx.playSFX("pling.wav");
				choix_option = choix_option + 1;
			}
			break;

		case '\r':
			switch (choix_option) {
			case 0:
				jouer.peser();
				sfx.playSFX("Select.wav");
				break;
			case 1:
				sfx.playSFX("Select.wav");
				audio.peser();
				break;
			case 2: //� compl�ter
				exit(0);
				break;
			case 3:
				quitter.peser();
				break;
			}
			break;
		}
		Sleep(20);
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

	while (true) {
		afficher(choix_option);
		touche_peser = _getch();

		switch (touche_peser) {
		case 'w':
			if (choix_option == 0) {
			choix_option = 0;
			
		}
		
			else {
				sfx.playSFX("pling.wav");
				choix_option = choix_option - 1;
			}
			break;
		case 's':
			if (choix_option == 1)
				choix_option = 1;
			else
			{
				sfx.playSFX("pling.wav");
				choix_option = choix_option + 1;
				
			}
			
			break;

		case '\r':

			
			switch (choix_option) {
			case 0:
				MainMenuOn = false;
				sfx.playSFX("Select.wav");
				//music2.setVolume(500);
				//music2.playMusic("OceanWorld.wav");
				jeux.executionJeu();
				return;
			case 1:
				menu_principal.peser();
				return;
			}
		}
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

	while (true) {
		afficher(choix_option);
		touche_peser = _getch();

		switch (touche_peser) {
		case 'w':
			if (choix_option == 0)
				choix_option = 0;
			else
			{
				choix_option = choix_option - 1;
				sfx.playSFX("pling.wav");
			}
			break;

		case 's':
			if (choix_option == 1)
				choix_option = 1;
			else
			{
				choix_option = choix_option + 1;
				sfx.playSFX("pling.wav");
			}
			break;

		case '\r':
			switch (choix_option) {
			case 0:
				exit(0);
			case 1:
				menu_principal.peser();
				return;
			}
		}
	}
}

void Audio::afficher(int choix_option) {
	const int taille_menu_audio = 1;
	string menu[taille_menu_audio] = { "MUSIQUE: " };
	system("cls");

	cout << "===== AUDIO =====" << endl;

	for (int i = 0; i < taille_menu_audio; i++) {
		if (i == choix_option) {
			cout << "* ";
		}
		cout << menu[i] << volume << endl;
	}
	cout << "==================" << endl;
}

void Audio::peser() {
	int choix_option = 0;
	char touche_peser;
	Sleep(200);
	while (true) 
	{
		afficher(choix_option);
		touche_peser = _getch();

		switch (touche_peser) {
		case 'a':
			if (volume == 0)
				volume = 0;
			else
				diminuer_volume();
			break;

		case 'd':
			if (volume == 100)
				volume = 100;
			else
				augmenter_volume();
			break;

		case '\r':
			switch (choix_option) {
			case 0:
				menu_principal.peser();
				return;
			}
		}
	}
}

void Audio::augmenter_volume() {
	volume = volume + 5;
	music.setVolume(volume);
}

void Audio::diminuer_volume() {
	volume = volume - 5;
	music.setVolume(volume);
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
