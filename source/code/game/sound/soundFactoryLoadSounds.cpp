#include "soundFactory.h"

void SoundFactory::NameToSound(std::string path, std::string name) {
	std::vector<std::pair<std::string, SoundEnum>> table{
		{"Player_bump.ogg", SoundEnum::Bump}
	};

	for (auto curr : table)
		if (curr.first == name) {
			sf::SoundBuffer buffer;
			try {
				buffer.loadFromFile(path + "/" + name);
			}
			catch (...) {
				Logger::error("class SoundFactory", __func__, "Couldn't load " + path + "/" + name + ". Aborting.");
				return;
			}

			auto pair = std::make_pair(sf::Sound(), buffer);
			sounds.insert(std::pair<SoundEnum, std::pair<sf::Sound, sf::SoundBuffer>>(curr.second, pair));

			auto it = sounds.find(curr.second);
			it->second.first.setBuffer(it->second.second);
			return;
		}
}

std::vector<std::string> read_directory(const std::string& name)
{
	std::string pattern(name);
	pattern.append("\\*");

	std::vector<std::string> files;

	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			files.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	return files;
}

void SoundFactory::loadSounds(std::string path) {
	std::vector<std::string> files = read_directory(path);

	for (auto str : files)
		NameToSound(path, str);
	Logger::debug_info("class SoundFactory", __func__, "Successfully loaded " + std::to_string(sounds.size()) + " sounds.");
}