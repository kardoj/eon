#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "configuration.h"
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
    Configuration configuration;

    setlocale(LC_CTYPE, "");

    // The first argument is always the program name
    if (argc < 2)
    {
        cout << "No command entered, nothing to do." << endl;
        return 0;
    }

    if (!command_is(INIT, argv) && !Tree::is_eon_dir())
    {
        cout << "Directory is not an eon directory.\nRun eon init to make it one." << endl;
        return 0;
    }

    if (!command_is(INIT, argv)) configuration = Configuration();

    if (command_is(ADD, argv))
    {
        if (argc < 5) {
            cout << "Required parameters are missing (eon add <start_time> <end_time> <description>). Nothing to do."
                 << endl;
            return 0;
        } else {
            if (Entry::add(argv[2], argv[3], argv[4], configuration.get_date(), configuration.get_project_id()))
            {
                cout << "A new entry was added: TODO: show by id" << endl;
            }
        }
    }
    else if (command_is(INIT, argv))
    {
        if (Tree::is_eon_dir())
        {
            cout << "Directory is already an eon directory." << endl;
        }
        else
        {
            if (Tree::init()) {
                cout << "Created a new eon directory." << endl;
            }
            else
            {
                cout << "Something went wrong while setting up eon." << endl;
            }
        }
    }
    else if (command_is(ADD_PROJECT, argv))
    {
        if (argc < 3)
        {
            cout << "No project name entered, nothing to do." << endl;
        }
        else
        {
            if (Project::add(argv[2]))
            {
                cout << "New project \"" << argv[2] << "\" was added." << endl;
            }
            else
            {
                cout << "There was a problem adding a new project." << endl;
            }
        }
    }
    else if (command_is(PROJECTS, argv))
    {
        Project::list(configuration.get_project_id());
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
