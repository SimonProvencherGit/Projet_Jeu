#include "globalobjects.h"

// Define global objects

//Test image avion
//
SFX sfx;
Music music;
SFX sfxWarning;
QGraphicsScene * GameScene = nullptr;
QGraphicsPixmapItem* player1;
QRect * basicbullet;
 // Players thats a square



// Ajouter toute les objets SFX pour gerer leurs volumes
void setallSFXVolume(float inputvolume)
{      
    sfxWarning.setVolume(inputvolume);

    sfx.setVolume(inputvolume);

}//System de sauvegard des settings
void savesettings() {
    std::ofstream outFile("Settings.txt");
    if (outFile.is_open()) {
        outFile << "SFXVOLUME:" << sfx.getvolume() << std::endl;
        outFile << "MUSICVOLUME:" << music.getvolume() << std::endl;
        outFile.close();
    }
    else {
        std::cout << "Erreur d'ouverture du fichier " << std::endl;
    }
}

 

void loadsettings() { 
    //just testing addition of square that an move


    // Add the rectangle to the scene
    //
    std::ifstream inFile("Settings.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) { //https://www.digitalocean.com/community/tutorials/getline-in-c-plus-plus
            if (line.find("SFXVOLUME:") == 0) {
                setallSFXVolume(std::stof(line.substr(10)));//https://www.geeksforgeeks.org/convert-string-to-int-in-cpp + converter le string a un float (stof)
            }
            else if (line.find("MUSICVOLUME:") == 0) {
                music.setVolume(std::stof(line.substr(12)));
            }
        }
        inFile.close();
    }
    else {
        std::cout << "Erreur aucun fichier trouv�, r�initialisation des r�glages" << std::endl;
        savesettings();
    }
}