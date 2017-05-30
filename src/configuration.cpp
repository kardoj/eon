#include <configuration.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>

Configuration::Configuration()
{
    read_config();
}

Configuration::~Configuration() {}

void Configuration::read_config()
{
    FILE *fp;
    int row_length = 100;
    char row[row_length];
    string row_str, key, value;

    fp = fopen("./eondata/config.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {
            if (fgets(row, row_length, fp) == NULL) break;
            row_str = string(row);
            int split_pos = row_str.find_first_of("=");
            if (split_pos == -1)
            {
                cout << "A line in the configuration file is missing an equals sign.";
                break;
            }
            else
            {
                key = row_str.substr(0, split_pos);
                value = row_str.substr(split_pos + 1);

                set_without_writing(key, value);
            }
        }
        fclose(fp);
    }
    else
    {
        cout << "There was a problem reading the configuration file.";
    }
}

void Configuration::set_without_writing(string key, string value)
{
    if (key.compare(string("date")) == 0)
    {
        this->dte = value;
    }
    else if (key.compare(string("project_id")) == 0)
    {
        int val = atoi(value.c_str());
        this->project_id = val;
    }
}

string Configuration::get_date()
{
    return this->dte;
}

int Configuration::get_project_id()
{
    return this->project_id;
}
