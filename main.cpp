#include <ctime>
#include <tree.h>
#include <iostream>
#include <project.h>
#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    time_t t;
    tm *local;
    int year, month, day, hour, minute, second;
    char datetime[20];
    Tree *tree;
    Project *project;

    // The first argument is always the program name
    if (argc < 2)
    {
        cout << "No command entered, nothing to do.";
        return 0;
    }

    if (!(((string) "init").compare(argv[1]) == 0) && !tree->is_timr_dir())
    {
        cout << "Directory is not a timr directory. Run timr init to make it one.";
        return 0;
    }

    // Set current date and time
    t = time(0);
    local = localtime(&t);
    year = local->tm_year + 1900;
    month = local->tm_mon + 1;
    day = local->tm_mday;
    hour = local->tm_hour;
    minute = local->tm_min;
    second = local->tm_sec;
    sprintf(datetime, "%d-%d-%d_%d:%d:%d", year, month, day, hour, minute, second);

    if (((string) "add").compare(argv[1]) == 0)
    {
        cout << "Running the add command";
    }
    else if (((string) "init").compare(argv[1]) == 0)
    {
        tree = new Tree();
        if (tree->is_timr_dir())
        {
            cout << "Directory is already a timr directory.";
        }
        else
        {
            if (tree->init()) {
                cout << "Created a new timr directory.";
            }
            else
            {
                cout << "Something went wrong while setting up timr.";
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
            project = new Project();
            if (project->add(argv[2], datetime))
            {
                cout << "New project " << argv[2] << " was added.";
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
