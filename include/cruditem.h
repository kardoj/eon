#ifndef CRUDITEM_H
#define CRUDITEM_H

#include <string>

using namespace std;

class CrudItem
{
    public:
        static const unsigned MAX_ID_LENGTH = 13;

        CrudItem();
        virtual ~CrudItem();

    protected:
        static string get_next_id_and_increment(const string path, const string file_open_error);
};

#endif // CRUDITEM_H
