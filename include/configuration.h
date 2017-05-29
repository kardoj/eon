#include <string>
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

using namespace std;

class Configuration
{
    public:
        Configuration();
        virtual ~Configuration();
        string get_date();
        void set_date();
        int get_project_id();
        int set_project_id();

    protected:

    private:
        string dte;
        int project_id;
        void read_config();

        // Sets the instance variable without writing it to file
        void set_without_writing(string key, string value);
};

#endif // CONFIGURATION_H
