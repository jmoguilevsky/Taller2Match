//
// Created by seba on 27/04/16.
//

#include "logger.h"

//const std::string levels[] = {"ERROR", "WARN", "INFO", "DEBUG"};

// Obtener la fecha y hora actual. Formato YYYY-MM-DD.HH:mm:ss.
const std::string fechaHora() {
    time_t ahora = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&ahora);
    strftime(buf, sizeof(buf), "[%Y-%m-%d.%X] ", &tstruct);

    return buf;
}

void Logger::logMessage(const std::string message, int type) {
    //Si el tipo de mensaje es menor o igual que el nivel de logeo, entonces se escribe el mensaje.
    if (type <= level) {
        std::fstream logfile;
        logfile.open(path.c_str(), std::fstream::app | std::fstream::out);
        logfile << fechaHora();
        logfile << message;
        logfile << std::endl;
        logfile.close();
    }
}

Logger::Logger(int level, std::string path) {
    this->level = level;
    this->path = path;
    logLevels.push_back("ERROR");
    logLevels.push_back("WARN");
    logLevels.push_back("INFO");
    logLevels.push_back("DEBUG");

    std::fstream logfile;
    logfile.open(path.c_str(), std::fstream::app | std::fstream::out | std::ios::out);
    logfile << "\n";
    logfile << "-----------------------------------" << "NIVEL " << logLevels[level] <<
    "--------------------------------------" << std::endl;
    logfile << "\n";
    logfile.close();
}
