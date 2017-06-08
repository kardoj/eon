#include <ctime>
#include <iostream>

#include "date.h"

using namespace std;

Date::Date(string dte) {
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
        this->dte = dte;
        year = mon = day = -1;
        valid = false;
        return;
    }

    time_t t = time(0);
    tm *local = localtime(&t);

    int year_val = year - 1900;
    int mon_val = mon - 1;

    local->tm_year = year_val;
    local->tm_mon = mon_val;
    local->tm_mday = day;

    mktime(local);

    if (local->tm_year == year_val || local->tm_mon == mon_val || local->tm_mday == day)
    {
        valid = true;
    } else {
        valid = false;
    }
}

Date::~Date() {}

bool Date::is_valid() { return valid; }

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

string Date::yyyy_mm_dd()
{
    char reformatted_date[11];
    sprintf(reformatted_date, "%d-%d-%d", year, mon, day);
    return string(reformatted_date);
}

