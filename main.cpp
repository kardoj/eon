#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "configuration.h"
#include "date.h"
#include "eon.h"
#include "entry.h"
#include "project.h"
#include "tree.h"

using namespace std;

// All supported commands
const string ADD = "add";
const string ADD_PROJECT = "addproject";
const string DATE = "date";
const string INIT = "init";
const string PROJECTS = "projects";
const string SET = "set";

bool command_is(string command, char *argv[])
{
    return command.compare(argv[1]) == 0;
}

int main(int argc, char *argv[])
{
    Configuration configuration = Configuration();
    Eon eon = Eon(argc, argv);

    setlocale(LC_CTYPE, "");

    if (argc < 2)
    {
        cout << "No command entered, nothing to do." << endl;
        return 0;
    }

    if (!Tree::is_eon_dir() && !command_is(INIT, argv))
    {
        cout << "Directory is not an eon directory.\nRun eon init to make it one." << endl;
        return 0;
    }

    if (!command_is(INIT, argv)) configuration.read();

    if (command_is(ADD, argv))
    {
        eon.add_entry(configuration.get_date(), configuration.get_project_id());
        return 0;
    }
    else if (command_is(INIT, argv))
    {
        eon.init();
        return 0;
    }
    else if (command_is(ADD_PROJECT, argv))
    {
        eon.add_project();
        return 0;
    }
    else if (command_is(PROJECTS, argv))
    {
        eon.list_projects(configuration.get_project_id());
        return 0;
    }
    else if (command_is(DATE, argv))
    {
        cout << "Currently set date: " << configuration.get_date() << endl;
    }
    else if (command_is(SET, argv))
    {
        if (argc == 2)
        {
            cout << "No parameters supplied to set. Nothing to do." << endl;
            return 0;
        }

        vector<string> keys, values;

        unsigned next, argc_u;
        argc_u = argc;
        for(unsigned i = 2; i < argc_u; i++)
        {
            next = i + 1;
            if (next < argc_u)
            {
                keys.push_back(argv[i]);
                values.push_back(argv[next]);
                i = next;
            }
            else
            {
                cout << "Parsing the parameters failed. Nothing to do." << endl;
                return 0;
            }
        }

        unsigned key_count = keys.size();
        unsigned updated = 0;

        for (unsigned i = 0; i < key_count; i++)
        {
            if (configuration.set_from_param(keys.at(i), values.at(i))) updated++;
        }

        if (updated > 0 && configuration.write())
        {
            cout << "Found " << key_count << ", successfully updated " << updated << " key(s)." << endl;
        }
    }
    else
    {
        cout << "Unknown command \"" << argv[1] << "\". Nothing to do." << endl;
    }

    return 0;
}
