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

//! Log para errores, info, warning y debug
enum LogLevel {
    ERROR, WARNING, INFO, DEBUG
};
//! Logger
class Log {

    static LogLevel level;
    static std::string path;

public:
    //! Log con el tag "DEBUG"
    static void debug(const std::string &msg);
    //! Log con el tag "INFO"
    static void info(const std::string &msg);
    //! Log con el tag "ERROR"
    static void error(const std::string &msg);
    //! Log con el tag "WARNING"
    static void warning(const std::string &msg);



    //!Metodo para logear mensajes.
    //!Parametro message: el mensaje que se quiere logear.
    //!Parametro type: el tipo de mensaje que se esta logeando. Usar
    //!0 si se trata de un error, 1 para warning, 2 para info y 3 para debug.
    static void log(LogLevel type, const std::string &message);

    //!Constructor de la clase.
    //!Parametro level: entero para indicar el nivel con el que se quiere logear. El
    //!nivel marcado incluye todos los mensajes del nivel anterior. Usar 0 para fijar
    //!el nivel en error, 1 para warning (incluye los mensajes de error), 2 para info
    //!(incluye mensajes de error y warning) y 3 para debug (todos los mensajes).
    //!Parametro path: ruta del archivo donde se quiere loggear.
    static void init(std::string path, LogLevel level);
};

#endif //LOGGERTESTS_LOGGER_H
