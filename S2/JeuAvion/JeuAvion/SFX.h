#ifndef SFX_H
#define SFX_H

#include <SFML/Audio.hpp>
#include <string>

class SFX {
public:
    SFX();
    ~SFX();
    void playSFX(const std::string& sound);
    void stopSFX();
    void setVolume(float volume);
    void pause();
    float getvolume();

private:
    float volume = 100; 
    sf::SoundBuffer SoundBuffer;
    sf::Sound Sound;
};

#endif
