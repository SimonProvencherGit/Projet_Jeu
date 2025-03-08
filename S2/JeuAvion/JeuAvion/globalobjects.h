#ifndef GLOBALOBJECTS_H
#define GLOBALOBJECTS_H
#include <iostream>
#include <fstream>
#include <string>
#include "SFX.h"
#include "Music.h"



// Declare global objects
extern void setallSFXVolume(float inputvolume);
extern void savesettings();
extern void loadsettings();
extern SFX sfx;
extern Music music;
extern SFX sfxWarning;

#endif // GLOBALS_H
