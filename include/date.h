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
};

#endif // DATE_H
