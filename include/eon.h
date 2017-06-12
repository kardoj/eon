#ifndef EON_H
#define EON_H

#include <string>

class Eon
{
    public:
        Eon(int argc, char *argv[]);
        virtual ~Eon();
        bool add_entry(string dte, int project_id);
        bool add_project();
        bool init();
        bool list_projects(int project_id);

    private:
        int argc;
        char **argv;
};

#endif // EON_H
