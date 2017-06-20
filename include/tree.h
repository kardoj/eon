#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>

class Tree
{
    public:
        static const char *const ROOT_DIR;
        static const char *const CONFIG_FILE;
        static const char *const ENTRIES_DIR;
        static const char *const ENTRIES_ID_FILE;
        static const char *const PROJECTS_DIR;
        static const char *const PROJECTS_FILE;
        static const char *const PROJECTS_ID_FILE;

        static const std::string MSG_ALREADY_INITIALIZED;
        static const std::string MSG_ENTRIES_PROJECTS_DIR_FAILURE;
        static const std::string MSG_INIT_FAILURE;
        static const std::string MSG_INIT_SUCCESS;
        static const std::string MSG_ROOT_DIR_FAILURE;

        Tree();
        virtual ~Tree();
        static bool init(const std::string datetime, std::vector<std::string> &messages_human);
        static void initial_config_str(const std::string dte, char return_str[]);
        static bool is_eon_dir();
        static void ensure_year_dir(const std::string year);

    protected:
        static bool create_dir(const char path[]);
        static bool create_file(const char path[], const char data[]);
};

#endif // TREE_H
