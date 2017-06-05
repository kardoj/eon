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
    string error_msg = string("\"") + dte + string("\" is not a valid date.");

    // If the supplied string's length is less than 8, it can not be a valid date
    if (dte.size() < 8)
    {
        cout << error_msg << endl;
        return false;
    }

    // Using regex to validate the structure
    if (!regex_match(dte.c_str(), regex("^\\d\\d\\d\\d-\\d\\d?-\\d\\d?")))
    {
        cout << error_msg << endl;
        return false;
    }

    int mon_start = dte.find_first_of("-");
    int day_start = dte.find_last_of("-");
    int year = atoi(dte.substr(0, 4).c_str());
    int mon = atoi(dte.substr(mon_start + 1, day_start - mon_start - 1).c_str());
    int day = atoi(dte.substr(day_start + 1).c_str());

    // Second part must be a number greater than zero and less than or equal to 12
    if (mon < 1 || mon > 12)
    {
        cout << error_msg << endl;
        return false;
    }

    // Confirm that the supplied month has the supplied date (e.g. 29 Feb is not valid)
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
