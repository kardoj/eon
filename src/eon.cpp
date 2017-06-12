#include <iostream>
#include <string>
#include "entry.h"
#include "eon.h"
#include "project.h"
#include "tree.h"

using namespace std;

Eon::Eon(int argc, char *argv[]) {
    this->argc = argc;
    this->argv = argv;
}

Eon::~Eon() {}

bool Eon::init()
{
    if (Tree::is_eon_dir())
    {
        cout << "Directory is already an eon directory." << endl;
        return false;
    }

    if (Tree::init()) {
        cout << "Created a new eon directory." << endl;
        return true;
    }
    else
    {
        cout << "Could not create the required directories." << endl;
        return false;
    }
}

bool Eon::add_entry(string dte, int project_id)
{
    if (argc == 5)
    {
        char p_id[Project::MAX_ID_LENGTH];
        sprintf(p_id, "%d", project_id);

        if (Entry::add(dte, p_id, argv[2], argv[3], argv[4]))
        {
            cout << "A new entry was added: TODO: show by id" << endl;
            return true;
        }
        return false;
    }
    else if (argc >= 7)
    {
        if (Entry::add(argv[2], argv[3], argv[4], argv[5], argv[6]))
        {
            cout << "A new entry was added: TODO: show by id" << endl;
            return true;
        }
        return false;
    }

    cout << "Required parameters are missing:\n"
         << "eon add <start_time> <end_time> <description>\n"
         << "eon add <date> <project_id|project_name|\"multi word project name\"> "
         << "<start_time> <end_time> <description>\nNothing to do."
         << endl;
    return false;
}

bool Eon::add_project()
{
    if (argc < 3)
    {
        cout << "No project name entered, nothing to do." << endl;
        return false;
    }

    if (Project::add(argv[2]))
    {
        cout << "New project \"" << argv[2] << "\" was added." << endl;
        return true;
    }
    else
    {
        cout << "There was a problem adding a new project." << endl;
        return false;
    }
}

bool Eon::list_projects(int project_id)
{
    Project::list(project_id);
    return true;
}

bool Eon::display_set_date(string dte)
{
    cout << "Currently set date: " << dte << endl;
    return true;
}
