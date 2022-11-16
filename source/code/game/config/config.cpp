#include "config.h"


int Config::windowHeight;
int Config::windowWidth;
float Config::musicVolume;
float Config::soundVolume;
float Config::windowCentreX = 0;
float Config::windowCentreY = 0;
float Config::windowSizeX = 0;
float Config::windowSizeY = 0;



void Config::InitConf(json data) {
	SetParam("windowWidth", data["window"]);
	SetParam("windowHeight", data["window"]);
	SetParam("musicVolume", data["window"]);
	SetParam("soundVolume", data["window"]);
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