#include "configuration.h"

#ifndef PROJECT_H
#define PROJECT_H

class Project
{
    public:
        static const char *DEFAULT_PROJECT_NAME;
        static const int MAX_PROJECT_ROW_LENGTH = 300;

        Project();
        virtual ~Project();
        static bool add(char name[], char dte[], char tme[]);
        static bool exists(int project_id);
        static bool list_projects(Configuration &config);
};

#endif // PROJECT_H
