#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "date.h"
#include "entry.h"
#include "eon.h"
#include "project.h"
#include "tree.h"

using namespace std;

Eon::Eon(const int argc, const char *argv[]) {
    this->argc = argc;
    this->argv = argv;
    Configuration configuration = Configuration();
}

Eon::~Eon() {}

bool Eon::init()
{
    Tree t;
    bool result = t.init(Date::current_date_with_time());
    format_output(t.get_messages());
    return result;
}

bool Eon::add_entry()
{
    if (argc == 5)
    {
        char p_id[Project::MAX_PROJECT_ID_LENGTH];
        sprintf(p_id, "%d", get_configuration().get_project_id());

        if (Entry().add(get_configuration().get_date(), p_id, argv[2], argv[3], argv[4]))
        {
            cout << "A new entry was added: TODO: show by id" << endl;
            return true;
        }
        return false;
    }
    else if (argc >= 7)
    {
        if (Entry().add(argv[2], argv[3], argv[4], argv[5], argv[6]))
        {
            cout << "A new entry was added: TODO: show by id" << endl;
            return true;
        }
        return false;
    }

    cout << "Required parameters are missing:\n"
         << "eon add <start:time> <end:time> <description>\n"
         << "eon add <date> <project_id|project_name|\"multi word project name\"> "
         << "<start:time> <end:time> <description>\nNothing to do."
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

    Project p;
    bool result = p.add(argv[2], Date::current_date_with_time());
    format_output(p.get_messages());
    return result;
}

bool Eon::display_set_date()
{
    cout << "Currently set date: " << get_configuration().get_date() << endl;
    return true;
}

void Eon::format_output(const vector<string> rows)
{
    unsigned row_count = rows.size();
    for (unsigned i = 0; i < row_count; i++)
    {
        cout << rows.at(i) << endl;
    }
}

bool Eon::list_projects()
{
    Project p;
    p.list(get_configuration().get_project_id());
    format_output(p.get_messages());
    return true;
}

bool Eon::set_parameters()
{
    if (argc == 2)
    {
        cout << "No parameters supplied to set. Nothing to do." << endl;
        return false;
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
            return false;
        }
    }

    unsigned key_count = keys.size();
    unsigned updated = 0;
    Configuration conf = get_configuration();

    for (unsigned i = 0; i < key_count; i++)
    {
        if (conf.set_from_param(keys.at(i), values.at(i))) updated++;
    }

    if (updated > 0 && conf.write())
    {
        format_output(conf.get_messages());
        return true;
    }
    format_output(conf.get_messages());
    return false;
}

Configuration Eon::get_configuration()
{
    if (!configuration.has_been_read())
    {
        configuration.read();
    }
    return configuration;
}
