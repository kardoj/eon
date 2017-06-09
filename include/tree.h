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
        static bool init(char dte[], char tme[]);
        static bool is_eon_dir();
        static void ensure_year_dir(string year);
        static void ensure_month_dir(string year, string month);

    private:
        static bool create_file(char path[], char data[]);
        static void initial_config_str(char dte[], char *return_str);
};

#endif // TREE_H
