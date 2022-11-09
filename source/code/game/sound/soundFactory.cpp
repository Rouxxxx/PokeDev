#include "soundFactory.h"

SoundFactory::SoundFactory()
	: className(typeid(this).name()), volume(100)
{}

void SoundFactory::loadMusic(std::string path) {
	if (!music.openFromFile(path))
		Logger::error(className, __func__, "Couldn't load music from path " + path);
	Logger::debug_info(className, __func__, "Successfully loaded music from path " + path);
}

void SoundFactory::StartMusic() { music.play(); music.setLoop(true); }
void SoundFactory::StopMusic() { music.stop(); }