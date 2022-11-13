#pragma once

#include <SFML/Audio.hpp>
#include "../config/config.h"
#include "../../utils/Logger/logger.h"

enum SoundEnum {
	Bump
};


class SoundFactory {
public:
	SoundFactory();
	void loadSounds(std::string path);
	void loadMusic(std::string path);
	void StopMusic();
	void StartMusic();
	void SetMusicVolume(float vol);
	void SetSoundVolume(float vol);
	void StartSound(SoundEnum soundEnum);
private:
	void NameToSound(std::string path, std::string name);
	float musicVolume;
	float soundVolume;
	sf::Music music;
	std::map<SoundEnum, std::pair<sf::Sound, sf::SoundBuffer>> sounds;
	sf::Sound sound;
	sf::Sound bonkSound;
	sf::SoundBuffer buffer;
	std::string className;
};