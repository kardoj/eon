#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include "configuration.h"

class Project
{
    public:
        static const std::string MSG_ERROR_INVALID_PROJECT;
        static const std::string MSG_ERROR_OPENING_PROJECTS_FILE;

        static const char *const DEFAULT_PROJECT_NAME;
        static const unsigned MAX_PROJECT_ID_LENGTH = 13;
        static const unsigned MAX_PROJECT_ROW_LENGTH = 300;

        Project();
        virtual ~Project();
        bool add(const char name[], const std::string datetime, std::vector<std::string> &messages_human);
        static bool exists(
            const std::string project_id_or_name,
            int &project_id, std::vector<std::string> &messages_human
        );

        static bool list(const int selected_project_id);
        static std::string msg_not_a_valid_project(const std::string project_id_or_name);
        static std::string msg_project_added(const std::string name);

    private:
        virtual const char *projects_file();
        static std::string get_next_id(FILE *fp);
};

#endif // PROJECT_H
