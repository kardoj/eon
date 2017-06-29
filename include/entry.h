#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include "cruditem.h"

class Entry : public CrudItem
{
    public:
        Entry();
        virtual ~Entry();
        static bool add(
            const std::string dte,
            const std::string project_id_or_name,
            const std::string start_time,
            const std::string end_time,
            const std::string description
        );

    private:
        static const int MAX_MINUTES_LENGTH = 5;

        static std::string get_next_id_and_increment(const std::string path);
};

#endif // ENTRY_H
