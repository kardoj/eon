#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <vector>
#include "eonbase.h"

class Configuration : public EonBase
{
    public:
        // Known command line parameters to set command
        static const std::string DATE_PARAM_KEY;
        static const std::string DATE_PARAM_KEY_SHORT;
        static const std::string PROJECT_PARAM_KEY;
        static const std::string PROJECT_PARAM_KEY_SHORT;

        static const std::string MSG_INVALID_CONFIG_ROW;
        static const std::string MSG_ERROR_OPENING_CONFIG_FILE;

        static const int MAX_CONFIG_ROW_LENGTH = 100;

        Configuration();
        virtual ~Configuration();
        std::string get_date();
        bool set_date(std::string dte);
        int get_project_id();
        bool read();
        bool set_project_id(std::string project_id_or_name);
        bool set_from_param(std::string key, std::string value);
        bool write();

    private:
        virtual const char *config_file();
        bool hb_read; // If the configuration file has been read
        int project_id;
        std::string dte;
};

#endif // CONFIGURATION_H
