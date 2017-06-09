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
};

#endif // ENTRY_H
