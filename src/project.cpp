#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>

#include "date.h"
#include "project.h"
#include "tree.h"

using namespace std;

// The default project that will be created on init
const char *Project::DEFAULT_PROJECT_NAME = "General";

Project::Project() {}
Project::~Project() {}

bool Project::add(char name[])
{
    FILE *fp;
    int id_max_length = 13;
    char id_str[id_max_length];

    // Getting the id
    fp = fopen(Tree::PROJECTS_ID_FILE, "r");
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
    fp = fopen(Tree::PROJECTS_FILE, "a");
    if (fp != NULL)
    {
        string datetime = Date::current_date_with_time();
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
    fp = fopen(Tree::PROJECTS_ID_FILE, "w");
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

bool Project::exists(string project_id_or_name, int &project_id)
{
    FILE *fp = fopen(Tree::PROJECTS_FILE, "r");
    if (fp != NULL)
    {
        bool name_equals;
        char row[Project::MAX_PROJECT_ROW_LENGTH];
        int id_end_pos, name_end_pos, row_id;
        string row_str;
        while(!feof(fp))
        {
            if (fgets(row, Project::MAX_PROJECT_ROW_LENGTH, fp) == NULL) break;
            row_str = string(row);
            id_end_pos = row_str.find_first_of(" ");
            name_end_pos = row_str.find_first_of("\"", id_end_pos + 2);

            if (id_end_pos == -1 || name_end_pos == -1)
            {
                cout << "Found an invalid project entry in the projects file.";
                return false;
            }
            else
            {
                name_equals = row_str.substr(id_end_pos + 2, name_end_pos - id_end_pos - 2)
                                     .compare(project_id_or_name) == 0;
                row_id = atoi(row_str.substr(0, id_end_pos).c_str());
                if (row_id == atoi(project_id_or_name.c_str()) || name_equals)
                {
                    project_id = row_id;
                    return true;
                }
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

bool Project::list_projects(Configuration &config)
{
    FILE *fp;
    fp = fopen(Tree::PROJECTS_FILE, "r");
    if (fp != NULL)
    {
        char row[MAX_PROJECT_ROW_LENGTH], output_row[MAX_PROJECT_ROW_LENGTH];
        int id_end, name_end;
        string id, name, row_str, selected;
        while(!feof(fp))
        {
            if (fgets(row, Project::MAX_PROJECT_ROW_LENGTH, fp) == NULL) break;
            row_str = string(row);
            id_end = row_str.find_first_of(" ");
            name_end = row_str.substr(id_end + 1).find_last_of("\"");
            id = row_str.substr(0, id_end);
            name = row_str.substr(id_end + 2, name_end - id_end);

            if (atoi(id.c_str()) == config.get_project_id())
            {
                selected = "*";
            }
            else
            {
                selected = "";
            }

            sprintf(output_row, "%3s %3s %-100s", selected.c_str(), id.c_str(), name.c_str());
            cout << output_row << endl;
        }
        return true;
    }
    else
    {
        cout << "There was a problem opening the projects file.";
        return false;
    }
}
