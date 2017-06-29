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
        static const int MAX_ENTRY_ROW_LENGTH = 1000;

        static std::string build_id(const std::string year, const std::string month, const std::string previous_nr);
        static std::string get_nr_from_last_row_and_move_pointer_to_the_end(FILE *fp);
};

#endif // ENTRY_H
