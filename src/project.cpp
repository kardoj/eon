#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "date.h"
#include "project.h"
#include "tree.h"

using namespace std;

// The default project that will be created on init
const char *const Project::DEFAULT_PROJECT_NAME = "General";

const string Project::MSG_ERROR_OPENING_ID_FILE = "There was a problem opening projects id file. Nothing to do.";
const string Project::MSG_ERROR_OPENING_PROJECTS_FILE = "There was a problem opening the projects file. Nothing to do.";
const string Project::MSG_PROJECT_ADDED = "New project \"PROJECT_NAME\" was added.";

Project::Project() {}
Project::~Project() {}

bool Project::add(const char name[], const string datetime, vector<string> &messages_human)
{
    FILE *fp = fopen(Tree::PROJECTS_FILE, "a");
    if (fp != NULL)
    {
        string id = get_next_id_and_increment(Tree::PROJECTS_ID_FILE);
        if (id.compare("-1") == 0)
        {
            messages_human.push_back(MSG_ERROR_OPENING_ID_FILE);
            return false;
        }

        string line = id + " \"" + string(name) + "\" " + datetime + " " + datetime + "\n";
        fputs(line.c_str(), fp);
        fclose(fp);
        messages_human.push_back(MSG_PROJECT_ADDED);
        return true;
    }
    else
    {
        messages_human.push_back(MSG_ERROR_OPENING_PROJECTS_FILE);
        return false;
    }
}

bool Project::exists(const string project_id_or_name, int &project_id)
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

bool Project::list(const int selected_project_id)
{
    FILE *fp = fopen(Tree::PROJECTS_FILE, "r");

    if (fp != NULL)
    {
        char row[MAX_PROJECT_ROW_LENGTH], output_row[MAX_PROJECT_ROW_LENGTH];
        int name_start;
        string id, name, row_str, selected;

        while(!feof(fp))
        {
            if (fgets(row, Project::MAX_PROJECT_ROW_LENGTH, fp) == NULL) break;
            row_str = string(row);
            id = row_str.substr(0, row_str.find_first_of(" "));
            name_start = row_str.find_first_of("\"") + 1;
            name = row_str.substr(name_start, row_str.find_last_of("\"") - name_start);

            if (atoi(id.c_str()) == selected_project_id)
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

string Project::get_next_id_and_increment(const string path)
{
    return CrudItem::get_next_id_and_increment(path);
}
