#include <add.h>
#include <ctime>
#include <dirtree.h>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    time_t t = time(0);
    tm *local = localtime(&t);
    int month, year;
    DirTree *tree = new DirTree();

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

    // Set current month and year
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;

    if (((string) "add").compare(argv[1]) == 0)
    {
        cout << "Running the add command" << endl;
    }
    else if (((string) "init").compare(argv[1]) == 0)
    {
        if (tree->is_timr_dir()) {
            cout << "Directory is already a timr directory.";
        } else {
            tree->init();
            cout << "Created a new timr directory.";
        }
    }
    else
    {
        cout << "Unknown command, nothing to do.";
    }

    return 0;
}
