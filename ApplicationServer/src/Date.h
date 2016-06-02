//
// Created by chris on 25/05/16.
//

#ifndef APPSERVER_DATE_H
#define APPSERVER_DATE_H

#include <ctime>
#include <string>
#include <iostream>

//! Para manejarse con las fechas.

class Date {
    struct tm date;
public:
    //! Devuelve un Date con la fecha del día de hoy.
    static Date today();

    Date();

    //! Construye un Date a partir de un string con el formato "dd/mm/yyyy".
    Date(std::string str);

    //! Construye un Date a partir del día, el mes y el año (>1900).
    Date(int day, int month, int year);

    //! Devuelve la fecha como un string con formato "dd/mm/yyyy"
    std::string str();

    //! Operador de comparación "<"
    friend bool operator<(const Date &lhs, const Date &rhs);

};

#endif //APPSERVER_DATE_H
