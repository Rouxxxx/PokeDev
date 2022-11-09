#pragma once

#include <SFML/Audio.hpp>
#include "../../utils/Logger/logger.h"


class SoundFactory {
public:
	SoundFactory();
	void loadMusic(std::string path);
	void StopMusic();
	void StartMusic();
	void SetVolume(float vol) { volume = vol; };
private:
	float volume;
	sf::Music music;
	sf::Sound sound;
	sf::Sound bonkSound;
	sf::SoundBuffer buffer;
	std::string className;
};