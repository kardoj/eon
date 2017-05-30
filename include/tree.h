#ifndef TREE_H
#define TREE_H

class Tree
{
    public:
        const static char *ROOT_DIR;
        const static char *CONFIG_FILE;
        const static char *ENTRIES_DIR;
        const static char *ENTRIES_ID_FILE;
        const static char *PROJECTS_DIR;
        const static char *PROJECTS_FILE;
        const static char *PROJECTS_ID_FILE;

        Tree();
        virtual ~Tree();
        static bool init(char dte[], char tme[]);
        static bool is_eon_dir();

    protected:

    private:
        static bool create_file(char path[], char data[]);
        static void initial_config_str(char dte[], char *return_str);
};

#endif // TREE_H
