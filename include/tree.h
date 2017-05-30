#ifndef TREE_H
#define TREE_H

class Tree
{
    public:
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
