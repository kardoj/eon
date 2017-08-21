#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <vector>

class Configuration
{
    public:
        // Known command line parameters to set command
        static const std::string DATE_PARAM_KEY;
        static const std::string DATE_PARAM_KEY_SHORT;
        static const std::string PROJECT_PARAM_KEY;
        static const std::string PROJECT_PARAM_KEY_SHORT;

        static const int MAX_CONFIG_ROW_LENGTH = 100;

        Configuration();
        virtual ~Configuration();
        std::string get_date();
        bool set_date(std::string dte, std::vector<std::string> &messages_human);
        int get_project_id();
        bool has_been_read();
        void read();
        bool set_project_id(std::string project_id_or_name, std::vector<std::string> &messages_human);
        bool set_from_param(std::string key, std::string value, std::vector<std::string> &messages_human);
        bool write();

    private:
        // If the configuration file has been read
        bool hb_read;
        int project_id;
        std::string dte;
};

#endif // CONFIGURATION_H
