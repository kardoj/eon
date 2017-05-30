#include <configuration.h>
#include <ctime>
#include <tree.h>
#include <iostream>
#include <project.h>
#include <stdio.h>
#include <string>

using namespace std;

void set_date_and_time(char *dte, char *tme)
{
    time_t t = time(0);
    tm *local = localtime(&t);
    sprintf(dte, "%d-%d-%d", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday);
    sprintf(tme, "%d:%d:%d", local->tm_hour, local->tm_min, local->tm_sec);
}

int main(int argc, char* argv[])
{
    char dte[11], tme[9];
    Configuration *configuration;

    // The first argument is always the program name
    if (argc < 2)
    {
        cout << "No command entered, nothing to do.";
        return 0;
    }

    if ((((string) "init").compare(argv[1]) != 0) && !Tree::is_eon_dir())
    {
        cout << "Directory is not an eon directory.\nRun eon init to make it one.";
        return 0;
    }

    set_date_and_time(dte, tme);

    if (((string) "init").compare(argv[1]) != 0) configuration = new Configuration();

    if (((string) "add").compare(argv[1]) == 0)
    {
        cout << "Running the add command";
    }
    else if (((string) "init").compare(argv[1]) == 0)
    {
        if (Tree::is_eon_dir())
        {
            cout << "Directory is already an eon directory.";
        }
        else
        {
            if (Tree::init(dte, tme)) {
                cout << "Created a new eon directory.";
            }
            else
            {
                cout << "Something went wrong while setting up eon.";
            }
        }
    }
    else if (((string) "addproject").compare(argv[1]) == 0)
    {
        if (argc < 3)
        {
            cout << "No project name entered, nothing to do.";
        }
        else
        {
            if (Project::add(argv[2], dte, tme))
            {
                cout << "New project \"" << argv[2] << "\" was added.";
            }
            else
            {
                cout << "There was a problem adding a new project.";
            }
        }
    }
    else
    {
        cout << "Unknown command, nothing to do.";
    }

    return 0;
}
