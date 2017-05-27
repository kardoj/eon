#ifndef TREE_H
#define TREE_H

class Tree
{
    public:
        Tree();
        virtual ~Tree();
        bool init(char dte[], char tme[]);
        bool is_eon_dir();
        void ensure_data_dir(int year);

    protected:

    private:
        bool create_file(char path[], char data[]);
        void initial_config_str(char dte[], char *return_str);
};

#endif // TREE_H
