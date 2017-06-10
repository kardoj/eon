#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include "configuration.h"
#include "cruditem.h"

class Project : public CrudItem
{
    public:
        static const char *DEFAULT_PROJECT_NAME;
        static const int MAX_PROJECT_ROW_LENGTH = 300;

        Project();
        virtual ~Project();
        static bool add(char name[]);
        static bool exists(string project_id_or_name, int &project_id);
        static bool list(int selected_project_id);

        static string get_next_id_and_increment(string path, string file_open_error);
};

#endif // PROJECT_H
