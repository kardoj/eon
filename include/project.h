#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include "configuration.h"
#include "cruditem.h"

class Project : public CrudItem
{
    public:
        static const std::string MSG_ERROR_OPENING_ID_FILE;
        static const std::string MSG_ERROR_OPENING_PROJECTS_FILE;

        static const char *const DEFAULT_PROJECT_NAME;
        static const int MAX_PROJECT_ROW_LENGTH = 300;

        Project();
        virtual ~Project();
        bool add(const char name[], const std::string datetime, std::vector<std::string> &messages_human);
        static bool exists(const std::string project_id_or_name, int &project_id);
        static bool list(const int selected_project_id);

        static std::string get_next_id_and_increment(const std::string path);
        static std::string msg_project_added(const std::string name);

    private:
        virtual const char *projects_id_file();
        virtual const char *projects_file();
};

#endif // PROJECT_H
