#ifndef EON_H
#define EON_H

#include <string>

class Eon
{
    public:
        Eon();
        virtual ~Eon();
        bool add_entry(int argc, char *argv[], string dte, int project_id);
        bool init(int argc, char *argv[]);
};

#endif // EON_H
