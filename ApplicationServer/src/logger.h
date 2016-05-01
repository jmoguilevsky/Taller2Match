//
// Created by seba on 27/04/16.
//

#ifndef LOGGERTESTS_LOGGER_H
#define LOGGERTESTS_LOGGER_H


#include <fstream>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <time.h>

class Logger{

    int level;
    std::string path;
    std::vector<std::string> logLevels;

public:
    // Metodo para logear mensajes.
    //Parametro message: el mensaje que se quiere logear.
    //Parametro type: el tipo de mensaje que se esta logeando. Usar
    //0 si se trata de un error, 1 para warning, 2 para info y 3 para debug.
    void logMessage(std::string message, int type);

    //Constructor de la clase.
    //Parametro level: entero para indicar el nivel con el que se quiere logear. El
    //nivel marcado incluye todos los mensajes del nivel anterior. Usar 0 para fijar
    //el nivel en error, 1 para warning (incluye los mensajes de error), 2 para info
    //(incluye mensajes de error y warning) y 3 para debug (todos los mensajes).
    //Parametro path: ruta del archivo donde se quiere loggear.
    Logger(int level, std::string path);

};

#endif //LOGGERTESTS_LOGGER_H
