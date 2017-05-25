#ifndef DIRTREE_H
#define DIRTREE_H

class DirTree
{
    public:
        DirTree();
        virtual ~DirTree();
        void init();
        bool is_timr_dir();
        void ensure_data_dir(int year);

    protected:

    private:
};

#endif // TREE_H
