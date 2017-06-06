#include <ctime>
#include <iostream>
#include <regex>

#include "date.h"

using namespace std;

Date::Date() {}
Date::~Date() {}

// Currently supports date format yyyy-m(m)-d(d)
bool Date::is_valid(string dte)
{
    int year, mon, day;
    string error_msg = string("\"") + dte + string("\" is not a valid date.");

    // Using regex to validate the structure of the string
    if (regex_match(dte.c_str(), regex("^\\d\\d\\d\\d-\\d\\d?-\\d\\d?")))
    {
        get_values_from_yyyy_mm_dd(dte, year, mon, day);
    }
    else
    {
        cout << error_msg << endl;
        return false;
    }


    // Second part must be a number greater than zero and less than or equal to 12
    if (mon < 1 || mon > 12)
    {
        cout << error_msg << endl;
        return false;
    }

    // Confirm that the supplied month has the supplied date (e.g. 30 Feb is not valid)
    time_t t = time(0);
    tm *local = localtime(&t);

    local->tm_year = year - 1900;
    local->tm_mon = mon;
    local->tm_mday = day;

    if (mktime(local) == -1)
    {
        cout << error_msg << endl;
        return false;
    }

    return true;
}

void Date::get_values_from_yyyy_mm_dd(string dte, int &year, int &mon, int &day)
{
    int mon_start = dte.find_first_of("-");
    int day_start = dte.find_last_of("-");

    // Output
    year = atoi(dte.substr(0, 4).c_str());
    mon = atoi(dte.substr(mon_start + 1, day_start - mon_start - 1).c_str());
    day = atoi(dte.substr(day_start + 1).c_str());
}

