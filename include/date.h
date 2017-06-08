#include <regex>
#include <string>

using namespace std;

#ifndef DATE_H
#define DATE_H

class Date
{
    public:
        static const regex DATE_FORMAT_DD_MM_YYYY;
        static const regex DATE_FORMAT_YYYY_MM_DD;

        Date(string dte);
        virtual ~Date();
        bool is_valid();
        static void to_yyyy_mm_dd(string &dte);

    private:
        string dte;
        int year, mon, day;
        bool valid;

        static void values_from_dd_mm_yyyy(string dte, int &year, int &mon, int &day);
        static void values_from_yyyy_mm_dd(string dte, int &year, int &mon, int &day);
};

#endif // DATE_H
