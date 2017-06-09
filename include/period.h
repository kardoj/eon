#ifndef PERIOD_H
#define PERIOD_H

#include <string>

using namespace std;

class Period
{
    public:
        Period(string start_time, string end_time);
        virtual ~Period();

        bool is_valid();
        unsigned minutes();

    private:
        bool valid;
        int start_hours, start_minutes, end_hours, end_minutes;
        unsigned period_minutes;

        void diff_minutes();
};

#endif // PERIOD_H
