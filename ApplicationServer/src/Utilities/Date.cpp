//
// Created by chris on 25/05/16.
//

#include "Date.h"

Date::Date(int day, int month, int year) {
    // year >= 1900
    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;
    //mktime(&date);
}

std::string Date::str() {
    char buf[80];
    strftime(buf, sizeof(buf), "%d/%m/%Y", &date);
    return buf;
}

bool operator<(const Date &lhs, const Date &rhs) {
    if (lhs.date.tm_year != rhs.date.tm_year) return lhs.date.tm_year < rhs.date.tm_year;
    if (lhs.date.tm_mon != rhs.date.tm_mon) return lhs.date.tm_mon < rhs.date.tm_mon;
    if (lhs.date.tm_mday != rhs.date.tm_mday) return lhs.date.tm_mday < rhs.date.tm_mday;
    return false;
}

Date::Date(std::string str) {
    // str tiene el formato "dd/mm/yyyy"
    // si str es "" hace cualquier cosa
    const char *time_details = str.c_str();
    strptime(time_details, "%d/%m/%Y", &date);
    //mktime(&date);
}

Date::Date() {
    date.tm_mday = 1;
    date.tm_mon = 0;
    date.tm_year = 0;
}

Date Date::today() {
    time_t now = time(0);
    struct tm tstruct;
    tstruct = *localtime(&now);
    int day = tstruct.tm_mday;
    int month = tstruct.tm_mon + 1;
    int year = tstruct.tm_year + 1900;
    return Date(day, month, year);
}