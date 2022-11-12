#pragma once

#include <SFML/Audio.hpp>
#include "../config/config.h"
#include "../../utils/Logger/logger.h"


class SoundFactory {
public:
	SoundFactory();
	void loadMusic(std::string path);
	void StopMusic();
	void StartMusic();
	void SetMusicVolume(float vol);
	void SetSoundVolume(float vol);
private:
	float musicVolume;
	float soundVolume;
	sf::Music music;
	sf::Sound sound;
	sf::Sound bonkSound;
	sf::SoundBuffer buffer;
	std::string className;
};