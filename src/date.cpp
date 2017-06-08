#include <ctime>
#include <iostream>
#include <regex>

#include "date.h"

using namespace std;

const regex Date::DATE_FORMAT_DD_MM_YYYY = regex("^\\d\\d?.\\d\\d?.\\d\\d\\d\\d");
const regex Date::DATE_FORMAT_YYYY_MM_DD = regex("^\\d\\d\\d\\d-\\d\\d?-\\d\\d?");

Date::Date() {}
Date::~Date() {}

bool Date::is_valid(string dte)
{
    int year, mon, day;

    if (regex_match(dte, DATE_FORMAT_YYYY_MM_DD))
    {
        values_from_yyyy_mm_dd(dte, year, mon, day);
    }
    else if (regex_match(dte, DATE_FORMAT_DD_MM_YYYY))
    {
        values_from_dd_mm_yyyy(dte, year, mon, day);
    }
    else
    {
        cout << error_msg(dte) << endl;
        return false;
    }

    time_t t = time(0);
    tm *local = localtime(&t);

    local->tm_year = year - 1900;
    local->tm_mon = mon;
    local->tm_mday = day;

    // Confirm that the supplied month has the supplied date (e.g. 30 Feb is not valid)
    if (mktime(local) == -1)
    {
        cout << error_msg(dte) << endl;
        return false;
    }

    return true;
}

void Date::values_from_yyyy_mm_dd(string dte, int &year, int &mon, int &day)
{
    int mon_start = dte.find_first_of("-");
    int day_start = dte.find_last_of("-");

    year = atoi(dte.substr(0, 4).c_str());
    mon = atoi(dte.substr(mon_start + 1, day_start - mon_start - 1).c_str());
    day = atoi(dte.substr(day_start + 1).c_str());
}

void Date::values_from_dd_mm_yyyy(string dte, int &year, int &mon, int &day)
{
    int mon_start = dte.find_first_of(".") + 1;
    int year_start = dte.find_last_of(".") + 1;

    day = atoi(dte.substr(0, mon_start).c_str());
    mon = atoi(dte.substr(mon_start, year_start - mon_start + 1).c_str());
    year = atoi(dte.substr(year_start, 4).c_str());
}

void Date::to_yyyy_mm_dd(string &dte)
{
    if (regex_match(dte, DATE_FORMAT_YYYY_MM_DD)) return;

    if (regex_match(dte, DATE_FORMAT_DD_MM_YYYY))
    {
        int year, mon, day;
        values_from_dd_mm_yyyy(dte, year, mon, day);
        char reformatted_date[11];
        sprintf(reformatted_date, "%d-%d-%d", year, mon, day);
        dte = string(reformatted_date);
    }
    else
    {
        cout << error_msg(dte) << endl;
    }
}

string Date::error_msg(string dte)
{
    return string("\"") + dte + string("\" is not a valid date.");
}

