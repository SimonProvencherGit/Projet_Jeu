// JeuAvion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Interface.h"
#include "Menu.h"
#include "globalobjects.h"

int main() 
{
	//-------------------section port série-------------------
    /*char com_port[] = "\\\\.\\COM8";
    DWORD COM_BAUD_RATE = CBR_9600;
    SimpleSerial Serial(com_port, COM_BAUD_RATE);

    if (Serial.IsConnected()) {
        //do whatever
    }
    int reply_wait_time = 7;
    string syntax_type = "JSON";

    while (1)
    {
        string incoming = Serial.ReadSerialPort(reply_wait_time, syntax_type);
        cout << incoming << endl;
    }*/
    //-------------------section port série-------------------
    setConsoleSize();
    loadsettings();
    Gerer_Menu menu;
    menu.peser();
 

    return 0;
}