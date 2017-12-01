#ifndef DATE_H
#define DATE_H

#include <regex>
#include <string>

class Date
{
    public:
        Date(const std::string dte);
        virtual ~Date();
        bool is_valid();
        std::string yyyy_mm_dd();
        int get_month();
        int get_year();
        int get_day();
        int get_wday();
        static std::string get_date(std::string datetime);
        static std::string current_date();
        static std::string current_date_with_time();

    private:
        const std::regex DATE_FORMAT_DD_MM_YYYY = std::regex("^\\d\\d?.\\d\\d?.\\d\\d\\d\\d");
        const std::regex DATE_FORMAT_YYYY_MM_DD = std::regex("^\\d\\d\\d\\d-\\d\\d?-\\d\\d?");
        bool valid;
        int year, mon, day, wday;
        std::string dte;

        void values_from_dd_mm_yyyy(const std::string dte, int &year, int &mon, int &day);
        void values_from_yyyy_mm_dd(const std::string dte, int &year, int &mon, int &day);
};

#endif // DATE_H
