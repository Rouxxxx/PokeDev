#include "soundFactory.h"
#include <iostream>

SoundFactory::SoundFactory()
	: className(typeid(this).name()), musicVolume(Config::musicVolume), soundVolume(Config::soundVolume)
{}

void SoundFactory::loadMusic(std::string path) {
	if (!music.openFromFile(path))
		Logger::error(className, __func__, "Couldn't load music from path " + path);
	Logger::debug_info(className, __func__, "Successfully loaded music from path " + path);
}

void SoundFactory::StartMusic() { music.setVolume(musicVolume); music.play(); music.setLoop(true); }
void SoundFactory::StopMusic() { music.stop(); }

void SoundFactory::SetMusicVolume(float vol) {
	musicVolume = vol; 
	if (music.getStatus() != sf::Music::Stopped)
		music.setVolume(musicVolume);
};
void SoundFactory::SetSoundVolume(float vol) {
	soundVolume = vol;
	if (sound.getStatus() == sf::Sound::Playing)
		sound.setVolume(soundVolume);
};

void SoundFactory::StartSound(SoundEnum soundEnum) {
	auto it = sounds.find(soundEnum);
	if (it == sounds.end()) {
		Logger::error("class SoundFactory", __func__, "Tried to play unloaded sound. Aborting.");
		return;
	}
	if (it->second.first.getStatus() == sf::Sound::Playing)
		return;

	Logger::info(__func__, "playing sound");
	it->second.first.play();
}