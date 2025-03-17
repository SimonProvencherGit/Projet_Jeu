// JeuAvion.cpp : 
//


#include "Interface.h"
#include "Menu.h"
#include "globalobjects.h"
//#include "SimpleSerial.h"
//#include <json.hpp>

//using json = nlohmann::json;
                       


int main() 
{
    /*
	//-------------------section port serie-------------------
    // Ouvrir le port série
	HANDLE hSerial = CreateFile(L"COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);  // selectionne le port serie
    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << "Erreur d'ouverture du port série." << endl;
        return 1;
    }

    // Configurer les paramètres du port série
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cerr << "Impossible de lire l'état du port série." << endl;
        CloseHandle(hSerial);
        return 1;
    }
    dcbSerialParams.BaudRate = CBR_9600;  // Assure-toi que le baud rate est correct
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    // Lecture de données série
    char buffer[12];        //taille du buffer qu'on s'attends de recevoir
    DWORD bytesRead;
    string response;

    while (true) {
        if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) { // si des données sont disponibles
            buffer[bytesRead] = '\0';  // Terminer la chaîne
            response += buffer;

            // Nettoyer les caractères de retour chariot (\r) et de nouvelle ligne (\n)
            size_t pos;
            while ((pos = response.find("\r\n")) != string::npos) {
                string line = response.substr(0, pos);  // Extraire la ligne sans \r\n
                response.erase(0, pos + 2);  // Enlever la ligne traitée

                try {
                    // Parser le JSON
                    json jsonData = json::parse(line);
					// Afficher le JSON
                    cout << "JSON recu : " << jsonData.dump(4) << endl;
					dataManette[0] = jsonData["Joy"];
					dataManette[1] = jsonData["acc"];
					dataManette[2] = jsonData["but1"];
					dataManette[3] = jsonData["but2"];
					dataManette[4] = jsonData["but3"];
					dataManette[5] = jsonData["but4"];
                }
                catch (json::parse_error& e) {
                    cerr << "Erreur JSON : " << e.what() << endl;
                }
            }
        }
    }
    
    CloseHandle(hSerial);  // Fermer le port série
    */
    
    ////-------------------section port serie-------------------
    setConsoleSize();
    loadsettings();
    Gerer_Menu menu;
    menu.peser();
 
    return 0;
}