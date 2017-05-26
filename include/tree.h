#ifndef TREE_H
#define TREE_H

class Tree
{
    public:
        Tree();
        virtual ~Tree();
        bool init();
        bool is_timr_dir();
        void ensure_data_dir(int year);

    protected:

    private:
};

#endif // TREE_H
