#include "config.h"


int Config::windowHeight;
int Config::windowWidth;
float Config::musicVolume;
float Config::soundVolume;

void Config::InitConf() {

	std::string path = "resources/config.json";
	json data;
	try {
		std::ifstream f(path);
		data = json::parse(f);
	}
	catch (...) {
		Logger::error("Config", __func__, "Error when parsing " + path + ". Aborting.");
		exit(2);
	}

	SetParam("windowWidth", data);
	SetParam("windowHeight", data);
	SetParam("musicVolume", data);
	SetParam("soundVolume", data);
}

void Config::SetDefaultParam(std::string param) {
	if (param == "windowWidth")
		Config::windowWidth = 1034;
	else if (param == "windowHeight")
		Config::windowHeight = 800;
	else if (param == "musicVolume")
		Config::musicVolume = 100;
	else if (param == "soundVolume")
		Config::soundVolume = 100;
}
void Config::SetNormalParam(std::string param, json ref) throw() {
	if (param == "windowWidth")
		Config::windowWidth = ref["windowWidth"];
	else if (param == "windowHeight")
		Config::windowHeight = ref["windowHeight"];
	else if (param == "musicVolume")
		Config::musicVolume = ref["musicVolume"];
	else if (param == "soundVolume")
		Config::soundVolume = ref["soundVolume"];
}

void Config::SetParam(std::string param, json ref) {
	try {
		SetNormalParam(param, ref);
	}
	catch (...) {
		Logger::error("class Config", __func__, "Error trying to retrieve argument (" + param + ") in Config JSON. Loading default parameter.");
		SetDefaultParam(param);
	}
}