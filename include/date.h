#include <regex>
#include <string>

using namespace std;

#ifndef DATE_H
#define DATE_H

class Date
{
    public:
        Date(string dte);
        virtual ~Date();
        bool is_valid();
        string yyyy_mm_dd();

    private:
        const regex DATE_FORMAT_DD_MM_YYYY = regex("^\\d\\d?.\\d\\d?.\\d\\d\\d\\d");
        const regex DATE_FORMAT_YYYY_MM_DD = regex("^\\d\\d\\d\\d-\\d\\d?-\\d\\d?");
        bool valid;
        int year, mon, day;
        string dte;

        void values_from_dd_mm_yyyy(string dte, int &year, int &mon, int &day);
        void values_from_yyyy_mm_dd(string dte, int &year, int &mon, int &day);
};

#endif // DATE_H
