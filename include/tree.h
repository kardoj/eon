#ifndef TREE_H
#define TREE_H

#include <string>

class Tree
{
    public:
        static const char *ROOT_DIR;
        static const char *CONFIG_FILE;
        static const char *ENTRIES_DIR;
        static const char *ENTRIES_ID_FILE;
        static const char *PROJECTS_DIR;
        static const char *PROJECTS_FILE;
        static const char *PROJECTS_ID_FILE;

        Tree();
        virtual ~Tree();
        static bool init(const std::string datetime);
        static void initial_config_str(const std::string dte, char *return_str);
        static bool is_eon_dir();
        static void ensure_year_dir(const std::string year);

    private:
        static bool create_file(const char path[], const char data[]);
};

#endif // TREE_H
