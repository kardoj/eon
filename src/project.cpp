#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>

#include "project.h"

using namespace std;

// The default project that will be created on init
const char *Project::DEFAULT_PROJECT_NAME = "General";

Project::Project() {}
Project::~Project() {}

bool Project::add(char name[], char dte[], char tme[])
{
    FILE *fp;
    int id_max_length = 13;
    char id_str[id_max_length];

    // Getting the id
    fp = fopen("./eondata/projects/next_id.txt", "r");
    if (fp != NULL)
    {
        fgets(id_str, id_max_length, fp);
        fclose(fp);
    }
    else
    {
        return false;
    }

    // Saving the new project
    fp = fopen("./eondata/projects/projects.txt", "a");
    if (fp != NULL)
    {
        string datetime = "" + string(dte) + "_" + string(tme) + "";
        string line = string(id_str) + " \"" + string(name) + "\" " + datetime + " " + datetime + "\n";
        fputs(line.c_str(), fp);
        fclose(fp);
    }
    else
    {
        return false;
    }

    // Incrementing and writing the next id
    int next_id = atoi(id_str) + 1;
    fp = fopen("./eondata/projects/next_id.txt", "w");
    if (fp != NULL)
    {
        sprintf(id_str, "%d", next_id);
        fputs(id_str, fp);
        fclose(fp);
        return true;
    }
    else
    {
        return false;
    }
}

bool Project::exists(int project_id)
{
    FILE *fp;
    fp = fopen("./eondata/projects/projects.txt", "r");
    if (fp != NULL)
    {
        char row[Project::MAX_PROJECT_ROW_LENGTH];
        int first_space_pos;
        string row_str;
        while(!feof(fp))
        {
            if (fgets(row, Project::MAX_PROJECT_ROW_LENGTH, fp) == NULL) break;
            row_str = string(row);
            first_space_pos = row_str.find_first_of(" ");

            if (first_space_pos == -1)
            {
                cout << "Found a project row with no spaces.";
                return false;
            } else
            {
                if (atoi(row_str.substr(0, first_space_pos).c_str()) == project_id) return true;
            }
        }
        return false;
    }
    else
    {
        cout << "There was a problem opening the projects file.";
        return false;
    }
}
