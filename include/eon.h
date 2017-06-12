#ifndef EON_H
#define EON_H

#include <string>

class Eon
{
    public:
        Eon();
        virtual ~Eon();
        bool add_entry(int argc, char *argv[], string dte, int project_id);
};

#endif // EON_H
