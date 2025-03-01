#include "Music.h"
#include <iostream>
#include <chrono>

Music::Music() {
    music.setLooping(true);
}

Music::~Music() {
    ;
    if (musicThread.joinable()) {
        musicThread.join();
    }
}

void Music::playMusic(string song, int start, int end) {
    thread([this, song, start, end]() {
        if (music.getStatus() == sf::SoundSource::Status::Playing) {
            FadeOut();
        }
        if (!music.openFromFile("Music\\" + song)) {
            cout << "Erreur de lecture de musique" << endl;
        return;
    }
    music.setLoopPoints({ sf::milliseconds(start), sf::milliseconds(end) });
    music.play();
}).detach();
}



void Music::stopMusic() {
    music.stop();
}

void Music::setVolume(float inputvolume)
{
    music.setVolume(inputvolume);
    volume = inputvolume;
}

void Music::FadeOut() {
    for (int i = volume; i > 0; i = i - 1) {
        music.setVolume(i);
        this_thread::sleep_for(chrono::milliseconds(1));
    }
    music.setVolume(volume);
}

void Music::StopWithFade()
{
    FadeOut();
    music.stop();
}