//
// Created by chris on 25/05/16.
//

#ifndef APPSERVER_DATE_H
#define APPSERVER_DATE_H

#include <ctime>
#include <string>
#include <iostream>

class Date {
    struct tm date;
public:
    static Date today();

    Date();

    Date(std::string str);

    Date(int day, int month, int year);

    std::string str();

    friend bool operator<(const Date &lhs, const Date &rhs);

};

#endif //APPSERVER_DATE_H
