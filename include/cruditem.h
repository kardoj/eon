#ifndef CRUDITEM_H
#define CRUDITEM_H

#include <string>

class CrudItem
{
    public:
        static const unsigned MAX_ID_LENGTH = 13;

        CrudItem();
        virtual ~CrudItem();

    protected:
        static std::string get_next_id_and_increment(const std::string path);
};

#endif // CRUDITEM_H
