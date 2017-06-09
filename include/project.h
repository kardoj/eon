#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include "configuration.h"

class Project
{
    public:
        static const char *DEFAULT_PROJECT_NAME;
        static const int MAX_PROJECT_ROW_LENGTH = 300;

        Project();
        virtual ~Project();
        static bool add(char name[]);
        static bool exists(string project_id_or_name, int &project_id);
        static bool list_projects(Configuration &config);
};

#endif // PROJECT_H
