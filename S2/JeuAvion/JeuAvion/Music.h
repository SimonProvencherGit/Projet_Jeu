#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <SFML/Audio.hpp>
#include <thread>
using namespace std;
class Music {
public:
    Music();
    ~Music();
    void playMusic(string song, int start, int end);
    void stopMusic();
    void setVolume(float volume);
    void StopWithFade();

private:
    void FadeOut();
    sf::Music music;
    int volume = 100;
    std::thread musicThread;
};

#endif