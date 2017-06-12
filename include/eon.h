#ifndef EON_H
#define EON_H

#include <string>
#include "configuration.h"

class Eon
{
    public:
        Eon(int argc, char *argv[]);
        virtual ~Eon();
        bool add_entry(string dte, int project_id);
        bool add_project();
        bool display_set_date(string dte);
        bool init();
        bool list_projects(int project_id);
        bool set_parameters();

    private:
        int argc;
        char **argv;
        Configuration configuration;
        // Reads the configuration if it has not been read yet. This should be used for accessing the configuration.
        Configuration get_configuration();
};

#endif // EON_H
