#ifndef ENTRY_H
#define ENTRY_H

#include <string>

using namespace std;

class Entry
{
    public:
        Entry();
        virtual ~Entry();
        static bool add(string start_time, string end_time, string description, string dte, int project_id);

    private:
        static const int MAX_ID_LENGTH = 13;
        static const int MAX_MINUTES_LENGTH = 5;

        static string get_next_id_and_increment();
};

#endif // ENTRY_H
