#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>

#include "configuration.h"
#include "date.h"
#include "project.h"
#include "tree.h"

const string Configuration::DATE_PARAM_KEY = "--date";
const string Configuration::DATE_PARAM_KEY_SHORT = "-d";
const string Configuration::PROJECT_PARAM_KEY = "--project";
const string Configuration::PROJECT_PARAM_KEY_SHORT = "-p";

Configuration::Configuration() {}
Configuration::~Configuration() {}

void Configuration::read()
{
    char row[MAX_CONFIG_ROW_LENGTH];
    string row_str, key, value;

    FILE *fp = fopen(Tree::CONFIG_FILE, "r");
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
                cout << "A line in the configuration file is missing an equals sign." << endl;
                break;
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
    }
    else
    {
        cout << "There was a problem reading the configuration file." << endl;
    }
}

bool Configuration::write()
{
    FILE *fp;
    fp = fopen(Tree::CONFIG_FILE, "w");
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
        cout << "There was a problem opening the configuration file." << endl;
        return false;
    }
}

bool Configuration::set_from_param(string key, string value)
{
    if (key.compare(DATE_PARAM_KEY) == 0 || key.compare(DATE_PARAM_KEY_SHORT) == 0)
    {
        return set_date(value);
    }
    else if (key.compare(PROJECT_PARAM_KEY) == 0 || key.compare(PROJECT_PARAM_KEY_SHORT) == 0)
    {
        return set_project_id(value);
    }
    else
    {
        cout << "Unrecognized key \"" << key<< "\" was ignored." << endl;
        return false;
    }
}

int Configuration::get_project_id() { return project_id; }

bool Configuration::set_project_id(string project_id_or_name)
{
    int p_id;
    if (Project::exists(project_id_or_name, p_id))
    {
        project_id = p_id;
        return true;
    }
    else
    {
        cout << "Unknown project id or name \"" << project_id_or_name << "\" ignored." << endl;
        return false;
    }
}

string Configuration::get_date() { return dte; }

bool Configuration::set_date(string dte)
{
    Date d = Date(dte);
    if (d.is_valid())
    {
        this->dte = d.yyyy_mm_dd();
        return true;
    }
    else
    {
        cout << string("\"") + dte + string("\" is not a valid date.");
        return false;
    }
}
