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
        eon.display_set_date(configuration.get_date());
        return 0;
    }
    else if (command_is(SET, argv))
    {
        eon.set_parameters();
        return 0;
    }
    else
    {
        cout << "Unknown command \"" << argv[1] << "\". Nothing to do." << endl;
    }

    return 0;
}
