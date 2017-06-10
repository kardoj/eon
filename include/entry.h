#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include "cruditem.h"

using namespace std;

class Entry : public CrudItem
{
    public:
        Entry();
        virtual ~Entry();
        static bool add(string dte, string project_id_or_name, string start_time, string end_time, string description);

    private:
        static const int MAX_MINUTES_LENGTH = 5;

        static string get_next_id_and_increment(string path, string file_open_error);
};

#endif // ENTRY_H
