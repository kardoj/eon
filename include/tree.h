#include <string>
#ifndef TREE_H
#define TREE_H

using namespace std;

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
        bool create_file(string path, string data, bool add_nl = false);
        string initial_config_string(char dte[]);
};

#endif // TREE_H
