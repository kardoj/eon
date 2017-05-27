#include <cstdlib>
#include <iostream>
#include <project.h>
#include <stdio.h>
#include <string>

using namespace std;

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
        string datetime = string(dte) + "_" + string(tme);
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
