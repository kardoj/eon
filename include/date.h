#include <string>

using namespace std;

#ifndef DATE_H
#define DATE_H

class Date
{
    public:
        Date();
        virtual ~Date();
        static bool is_valid(string dte);

    private:
        static void get_values_from_yyyy_mm_dd(string dte, int &year, int &mon, int &day);
};

#endif // DATE_H
