#include "logger.h"

bool Logger::debugState = false;

static void print_colored(std::ostream *stream, std::string str, int colorID) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, colorID);
    *stream << str;
    SetConsoleTextAttribute(hConsole, 7);
}

void Logger::debug_info(std::string className, std::string name, std::string msg) {
    if (!debugState)
        return;
    info(className, name, msg);
}
void Logger::debug_info(std::string funcName, std::string msg) {
    if (!debugState)
        return;
    info(funcName, msg);
}

void Logger::info(std::string className, std::string name, std::string msg) {

    std::string finalName = className + "::" + name;
    info(finalName, msg);
}
void Logger::info(std::string funcName, std::string msg) {
    std::string timeStr = getTime();
    std::clog << timeStr << " [";
    print_colored(&std::clog, "INFO", 14);
    std::clog << "] [" << funcName << "] " << msg << std::endl;
}

void Logger::debug_error(std::string className, std::string name, std::string msg) {
    if (!debugState)
        return;
    error(className, name, msg);
}
void Logger::debug_error(std::string funcName, std::string msg) {
    if (!debugState)
        return;
    error(funcName, msg);
}

void Logger::error(std::string className, std::string name, std::string msg) {
    std::string finalName = className + "::" + name;
    error(finalName, msg);
}

void Logger::error(std::string funcName, std::string msg) {
    std::string timeStr = getTime();
    std::cerr << timeStr << " [";
    print_colored(&std::cout, "ERROR", 12);
    std::cerr << "] [" << funcName << "] " << msg << std::endl;
}





void Logger::debug_warn(std::string className, std::string name, std::string msg) {
    if (!debugState)
        return;
    warn(className, name, msg);
}
void Logger::debug_warn(std::string funcName, std::string msg) {
    if (!debugState)
        return;
    warn(funcName, msg);
}

void Logger::warn(std::string className, std::string name, std::string msg) {
    std::string finalName = className + "::" + name;
    warn(finalName, msg);
}
void Logger::warn(std::string funcName, std::string msg) {
    std::string timeStr = getTime();
    std::clog << timeStr << " [";
    print_colored(&std::clog, "WARN", 13);
    std::clog << "] [" << funcName << "] " << msg << std::endl;
}






std::string getGoodIntStr(int integer) {
    std::string intStr = std::to_string(integer);
    if (integer < 10)
        intStr.insert(0, "0");
    return intStr;
}

std::string Logger::getTime() {
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    int monthInt = 1 + newtime.tm_mon;
    int yearInt = newtime.tm_year + 1900;
    int dayInt = newtime.tm_mday;

    std::string year = getGoodIntStr(newtime.tm_year + 1900);
    std::string month = getGoodIntStr(1 + newtime.tm_mon);
    std::string day = getGoodIntStr(newtime.tm_mday);

    std::string hour = getGoodIntStr(newtime.tm_hour);
    std::string min = getGoodIntStr(newtime.tm_min);
    std::string sec = getGoodIntStr(newtime.tm_sec);

    return "[" + year + "-" + month + "-" + day + " " + hour + ":" + min + ":" + sec + "]";
}