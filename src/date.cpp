#include <iostream>

#include "date.h"

Date::Date() {}
Date::~Date() {}

// Currently supports date format yyyy-m(m)-d(d)
bool Date::is_valid(string dte)
{
    // If the supplied string's length is less than 8, it can not be a valid date
    if (dte.size() < 8)
    {
        cout << "\"" << dte << "\" is not a valid date." << endl;
        return false;
    }

    // It must have 2 hyphens and three numbers around them to be valid
    int mon_start, day_start;

    // First part must be a 4 digit number
    // Second part must be a number greater than zero and less than or equal to 12
    // Third part must be a number greater than zero and less than or equal to 31
    // Confirm that the supplied month has the supplied date (e.g. 29 Feb is not valid)
    return true;
}
