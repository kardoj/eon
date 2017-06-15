#ifndef EON_H
#define EON_H

#include <string>
#include <vector>
#include "configuration.h"

class Eon
{
    public:
        Eon(const int argc, const char *argv[]);
        virtual ~Eon();
        bool add_entry();
        bool add_project();
        bool display_set_date();
        bool init();
        bool list_projects();
        bool set_parameters();

    private:
        int argc;
        const char **argv;
        Configuration configuration;

        void format_output(const std::vector<std::string> rows);
        Configuration get_configuration();
};

#endif // EON_H
