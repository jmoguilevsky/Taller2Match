//
// Created by seba on 27/04/16.
//

#include "Log.h"


const std::string logLevelStr[] = {"ERROR", "WARNING", "INFO", "DEBUG"};
LogLevel Log::level = ERROR;
std::string Log::path = "";

// Obtener la fecha y hora actual. Formato YYYY-MM-DD.HH:mm:ss.
const std::string fechaHora() {
    time_t ahora = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&ahora);
    strftime(buf, sizeof(buf), "[%Y/%m/%d-%X] ", &tstruct);
    return buf;
}

void Log::debug(const std::string &msg) {
    log(DEBUG, msg);
}

void Log::error(const std::string &msg) {
    log(ERROR, msg);
}

void Log::info(const std::string &msg) {
    log(INFO, msg);
}

void Log::warning(const std::string &msg) {
    log(WARNING, msg);
}

void Log::log(LogLevel type, const std::string &message) {
    //Si el tipo de mensaje es menor o igual que el nivel de logeo, entonces se escribe el mensaje.
    if (type <= level) {
        std::fstream logfile;
        logfile.open(path.c_str(), std::fstream::app | std::fstream::out);
        logfile << fechaHora();
        logfile << logLevelStr[type] << " : ";
        logfile << message;
        logfile << std::endl;
    }
}

void Log::init(std::string path, LogLevel level) {
    Log::level = level;
    Log::path = path;
    std::fstream logfile;
    logfile.open(path.c_str(), std::fstream::app | std::fstream::out | std::ios::out);
    logfile << fechaHora() << " ***** New log session: " + logLevelStr[level] + " *****" << std::endl;
}