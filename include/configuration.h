#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

using namespace std;

class Configuration
{
    public:
        // Known command line parameters to set command
        static const string DATE_PARAM_KEY;
        static const string DATE_PARAM_KEY_SHORT;
        static const string PROJECT_PARAM_KEY;
        static const string PROJECT_PARAM_KEY_SHORT;

        static const int MAX_CONFIG_ROW_LENGTH = 100;

        Configuration();
        virtual ~Configuration();
        string get_date();
        bool set_date(string dte);
        int get_project_id();
        void read();
        bool set_project_id(string project_id_or_name);
        bool set_from_param(string key, string value);
        bool write();

    private:
        string dte;
        int project_id;
};

#endif // CONFIGURATION_H
