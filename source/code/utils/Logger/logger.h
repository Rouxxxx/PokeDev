#pragma once

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

enum LogType {
	info,
	error,
	warn
};

class Logger {
public:
	static void debug_info(std::string className, std::string name, std::string msg);
	static void debug_error(std::string className, std::string name, std::string msg);
	static void debug_warn(std::string className, std::string name, std::string msg);

	static void debug_info(std::string name, std::string msg);
	static void debug_error(std::string name, std::string msg);
	static void debug_warn(std::string name, std::string msg);


	static void info(std::string className, std::string name, std::string msg);
	static void error(std::string className, std::string name, std::string msg);
	static void warn(std::string className, std::string name, std::string msg);

	static void info(std::string name, std::string msg);
	static void error(std::string name, std::string msg);
	static void warn(std::string name, std::string msg);

	static void enableDebug() { debugState = true; }
	static void disableDebug() { debugState = false; }
	static bool debugState;
private:
	static std::string getTime();
	
};