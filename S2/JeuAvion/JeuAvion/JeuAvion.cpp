// JeuAvion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Interface.h"
#include "Menu.h"
#include "globalobjects.h"







int main() {
    //SFX sfx;
    //Music music;
    //music.setVolume(500);
    //music.playMusic("MainMenu.wav");
    //sfx.playSFX("Select.wav");
    //music.playMusic("OceanWorld.wav");
    setConsoleSize();
    loadsettings();
    Gerer_Menu menu;
    menu.peser();
    //Interface game;
    //game.executionJeu();

    return 0;
}