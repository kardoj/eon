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
        static bool add(
            const string dte,
            const string project_id_or_name,
            const string start_time,
            const string end_time,
            const string description
        );

    private:
        static const int MAX_MINUTES_LENGTH = 5;

        static string get_next_id_and_increment(const string path, const string file_open_error);
};

#endif // ENTRY_H
