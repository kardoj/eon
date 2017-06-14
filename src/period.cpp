#include <iostream>
#include <regex>
#include "period.h"

using namespace std;

Period::Period(const string start_time, const string end_time)
{
    regex pattern = regex("^([0-2]\\d?):([0-5]?\\d)");

    if (regex_match(start_time, pattern) && regex_match(end_time, pattern))
    {
        int start_split_pos = start_time.find_first_of(":");
        int end_split_pos = end_time.find_first_of(":");

        start_hours = atoi(start_time.substr(0, start_split_pos).c_str());
        start_minutes = atoi(start_time.substr(start_split_pos + 1).c_str());

        end_hours = atoi(end_time.substr(0, end_split_pos).c_str());
        end_minutes = atoi(end_time.substr(end_split_pos + 1).c_str());

        valid = true;

        diff_minutes();
    }
    else
    {
        valid = false;
        start_hours = start_minutes = end_hours = end_minutes = period_minutes = -1;
    }
}

Period::~Period() {}

bool Period::is_valid() { return valid; }

unsigned Period::minutes() { return period_minutes; }

void Period::diff_minutes()
{
    if (start_hours == end_hours)
    {
        period_minutes = end_minutes - start_minutes;
    }
    else if (end_hours < start_hours)
    {
        period_minutes = (24 - start_hours + end_hours) * 60 + end_minutes - start_minutes;
    }
    else
    {
        period_minutes = (end_hours - start_hours) * 60 + end_minutes - start_minutes;
    }
}


