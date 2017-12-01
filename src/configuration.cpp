#include <cstdlib>
#include <iostream>

#include "configuration.h"
#include "date.h"
#include "project.h"
#include "tree.h"

using namespace std;

const string Configuration::DATE_PARAM_KEY = "--date";
const string Configuration::DATE_PARAM_KEY_SHORT = "-d";
const string Configuration::PROJECT_PARAM_KEY = "--project";
const string Configuration::PROJECT_PARAM_KEY_SHORT = "-p";

const string Configuration::MSG_INVALID_CONFIG_ROW = "A line in the configuration file is missing an equals sign.";
const string Configuration::MSG_ERROR_OPENING_CONFIG_FILE = "There was a problem reading the configuration file.";

Configuration::Configuration() {
    read();
}

Configuration::~Configuration() {}

bool Configuration::read()
{
    char row[MAX_CONFIG_ROW_LENGTH];
    string row_str, key, value;

    FILE *fp = fopen(config_file(), "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {
            if (fgets(row, MAX_CONFIG_ROW_LENGTH, fp) == NULL) break;
            row_str = string(row);
            row_str.erase(row_str.end()-1);
            int split_pos = row_str.find_first_of("=");
            int nl_pos = row_str.find_first_of("\n");
            if (split_pos == -1)
            {
                add_message(MSG_INVALID_CONFIG_ROW);
                fclose(fp);
                // TODO: Maybe a repair routine to reset default configuration in case someone has manually edited it?
                return false;
            }
            else
            {
                key = row_str.substr(0, split_pos);
                value = row_str.substr(split_pos + 1, nl_pos);

                if (key.compare(string("date")) == 0)
                {
                    set_date(value);
                }
                else if (key.compare(string("project_id")) == 0)
                {
                    set_project_id(value);
                }
            }
        }
        fclose(fp);
        return true;
    }
    else
    {
        add_message(MSG_ERROR_OPENING_CONFIG_FILE);
        return false;
    }
}

const char *Configuration::config_file()
{
    return Tree::CONFIG_FILE;
}

bool Configuration::write()
{
    FILE *fp;
    fp = fopen(config_file(), "w");
    char row[MAX_CONFIG_ROW_LENGTH];
    if (fp != NULL)
    {
        // Write all the params one by one
        sprintf(row, "date=%s\n", dte.c_str());
        fputs(row, fp);

        sprintf(row, "project_id=%d\n", project_id);
        fputs(row, fp);

        fclose(fp);
        return true;
    }
    else
    {
        add_message("There was a problem opening the configuration file.");
        return false;
    }
}

bool Configuration::set_from_param(string key, string value)
{
    if (key.compare(DATE_PARAM_KEY) == 0 || key.compare(DATE_PARAM_KEY_SHORT) == 0)
    {
        bool ok = set_date(value);
        if (ok)
        {
            add_message("Date successfully set to " + value + ".");
        }
        else
        {
            add_message("\"" + dte + "\" is not a valid date.");
        }
        return set_date(value);
    }
    else if (key.compare(PROJECT_PARAM_KEY) == 0 || key.compare(PROJECT_PARAM_KEY_SHORT) == 0)
    {
        bool ok = set_project_id(value);
        if (ok)
        {
            add_message("Project successfully set to id/name " + value + ".");
        }
        else
        {
            add_message("Unknown project id/name " + value + " ignored.");
        }
        return ok;
    }
    else
    {
        add_message("Unrecognized key \"" + key + "\" was ignored.");
        return false;
    }
}

int Configuration::get_project_id() { return project_id; }

bool Configuration::set_project_id(string project_id_or_name)
{
    int p_id;
    Project p;

    if (p.exists(project_id_or_name, p_id))
    {
        project_id = p_id;
        return true;
    }
    else
    {
        return false;
    }
}

string Configuration::get_date() { return dte; }

bool Configuration::set_date(string dte)
{
    if (dte.compare("today") == 0)
    {
        dte = Date::current_date();
    }

    Date d = Date(dte);

    if (d.is_valid())
    {
        string dte_str = d.yyyy_mm_dd();
        this->dte = dte_str;
        return true;
    }
    else
    {
        return false;
    }
}
