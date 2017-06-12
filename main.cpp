#include <iostream>
#include <string>

#include "eon.h"
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
    setlocale(LC_CTYPE, "");
    Eon eon = Eon(argc, argv);

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

    if (command_is(ADD, argv))
    {
        eon.add_entry();
    }
    else if (command_is(INIT, argv))
    {
        eon.init();
    }
    else if (command_is(ADD_PROJECT, argv))
    {
        eon.add_project();
    }
    else if (command_is(PROJECTS, argv))
    {
        eon.list_projects();
    }
    else if (command_is(DATE, argv))
    {
        eon.display_set_date();
    }
    else if (command_is(SET, argv))
    {
        eon.set_parameters();
    }
    else
    {
        cout << "Unknown command \"" << argv[1] << "\". Nothing to do." << endl;
    }

    return 0;
}
