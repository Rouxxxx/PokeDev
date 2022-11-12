#pragma once

#include<fstream>
#include <SFML/Window/Keyboard.hpp>
#include "../../utils/json/json.hpp"
#include "../../utils/Logger/logger.h"

using json = nlohmann::json;
using reference = const nlohmann::json&;



class Config {
public:
	static void InitConf(json);
	static int windowHeight;
	static int windowWidth;
	static float musicVolume;
	static float soundVolume;
private:
	static void SetParam(std::string, json);
	static void SetNormalParam(std::string, json) throw();
	static void SetDefaultParam(std::string);
};