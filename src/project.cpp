#include <cstdlib>
#include <iostream>
#include <vector>
#include "project.h"
#include "tree.h"

using namespace std;

// The default project that will be created on init
const char *const Project::DEFAULT_PROJECT_NAME = "General";

const string Project::MSG_ERROR_INVALID_PROJECT = "Found an invalid project entry in the projects file.";
const string Project::MSG_ERROR_OPENING_PROJECTS_FILE = "There was a problem opening the projects file. Nothing to do.";
const string Project::MSG_ERROR_CREATING_PROJECTS_TEMP_FILE = "Could not create projects temp file. Nothing to do.";

Project::Project() {}
Project::~Project() {}

bool Project::add(const char name[], const string datetime, vector<string> &messages_human)
{
    FILE *fp = fopen(projects_file(), "a+");
    if (fp != NULL)
    {
        string id = get_next_id(fp);

        string line = id + " \"" + string(name) + "\" 0 " + datetime + " " + datetime + "\n";
        fputs(line.c_str(), fp);
        fclose(fp);
        messages_human.push_back(msg_project_added(name));
        return true;
    }
    else
    {
        messages_human.push_back(MSG_ERROR_OPENING_PROJECTS_FILE);
        return false;
    }
}

const char *Project::projects_file()
{
    return Tree::PROJECTS_FILE;
}

string Project::msg_project_added(const string name)
{
    return "New project \"" + name + "\" was added.";
}

string Project::msg_not_a_valid_project(const string project_id_or_name)
{
    return "Unknown project id or name \"" + project_id_or_name + "\" ignored.";
}

bool Project::exists(const string project_id_or_name, int &project_id, vector<string> &messages_human)
{
    project_id = -1;
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
            // TODO: Use split_project_row
            row_str = string(row);
            id_end_pos = row_str.find_first_of(" ");
            name_end_pos = row_str.find_first_of("\"", id_end_pos + 2);

            if (id_end_pos == -1 || name_end_pos == -1)
            {
                fclose(fp);
                messages_human.push_back(Project::MSG_ERROR_INVALID_PROJECT);
                return false;
            }
            else
            {
                name_equals = row_str.substr(id_end_pos + 2, name_end_pos - id_end_pos - 2)
                                     .compare(project_id_or_name) == 0;
                row_id = atoi(row_str.substr(0, id_end_pos).c_str());
                if (row_id == atoi(project_id_or_name.c_str()) || name_equals)
                {
                    fclose(fp);
                    project_id = row_id;
                    return true;
                }
            }
        }
        fclose(fp);
        messages_human.push_back(msg_not_a_valid_project(project_id_or_name));
        return false;
    }
    else
    {
        messages_human.push_back(Project::MSG_ERROR_OPENING_PROJECTS_FILE);
        return false;
    }
}

bool Project::list(const int selected_project_id, vector<string> &messages_human)
{
    FILE *fp = fopen(projects_file(), "r");

    if (fp != NULL)
    {
        char row[MAX_PROJECT_ROW_LENGTH], output_row[MAX_PROJECT_ROW_LENGTH];
        string id, name, selected, use_count, created_at, updated_at;

        while(!feof(fp))
        {
            if (fgets(row, Project::MAX_PROJECT_ROW_LENGTH, fp) == NULL) break;

            split_project_row(string(row), id, name, use_count, created_at, updated_at);
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
        messages_human.push_back(MSG_ERROR_OPENING_PROJECTS_FILE);
        return false;
    }
}

string Project::get_next_id(FILE *fp)
{
    char row[MAX_PROJECT_ROW_LENGTH] = { "0" };
    while (!feof(fp))
    {
        if (fgets(row, MAX_PROJECT_ROW_LENGTH, fp) == NULL) break;
    }

    string row_str = string(row);
    string id_str;

    if (row_str.compare("0") != 0)
    {
        id_str = row_str.substr(0, row_str.find_first_of(" "));
    }
    else
    {
        id_str = row_str;
    }

    char helper[MAX_PROJECT_ID_LENGTH];
    sprintf(helper, "%d", atoi(id_str.c_str()) + 1);
    return string(helper);
}

bool Project::update_use_count(const string project_id_or_name, const int change)
{
    FILE *fp_in = fopen(Tree::PROJECTS_FILE, "r");

    if (fp_in != NULL)
    {
        FILE *fp_out = fopen(Tree::PROJECTS_TEMP_FILE, "w");

        if (fp_out != NULL)
        {
            char row[MAX_PROJECT_ROW_LENGTH];
            string id, name, use_count, created_at, updated_at;
            bool found = false;
            while(!feof(fp_in))
            {
                if (fgets(row, MAX_PROJECT_ROW_LENGTH, fp_in) == NULL) break;
                // Check if this is the project row we are looking for
                split_project_row(row, id, name, use_count, created_at, updated_at);
                // If it is, change and write
                found = true;
                // If it is not, write
            }

            // Delete original projects file
            // Rename tempfile

            if (!found)
            {
                cout << msg_not_a_valid_project(project_id_or_name) << endl;
                fclose(fp_out);
                fclose(fp_in);
                return false;
            }
        }
        else
        {
            cout << MSG_ERROR_CREATING_PROJECTS_TEMP_FILE << endl;
            fclose(fp_in);
            return false;
        }

        fclose(fp_out);
        fclose(fp_in);
        return true;
    }
    else
    {
        cout << MSG_ERROR_OPENING_PROJECTS_FILE << endl;
        return false;
    }
}

void Project::split_project_row(
        const string row,
        string &id,
        string &name,
        string &use_count,
        string &created_at,
        string &updated_at)
{
    string search_str = row;
    int from = 0;
    int to = row.find_first_of(" ");
    id = row.substr(from, to);

    search_str = search_str.substr(to + 1);
    from = search_str.find_first_of("\"") + 1;
    to = search_str.find_last_of("\"");
    name = search_str.substr(from, to - from);

    search_str = search_str.substr(to + 1);
    from = search_str.find_first_of(" ") + 1;
    to = search_str.substr(from).find_first_of(" ");
    use_count = search_str.substr(from, to);

    search_str = search_str.substr(to + 1);
    from = search_str.find_first_of(" ") + 1;
    to = search_str.substr(from).find_first_of(" ");
    created_at = search_str.substr(from, to);

    search_str = search_str.substr(to + 1);
    from = search_str.find_first_of(" ") + 1;
    to = search_str.substr(from).find_first_of("\n");
    updated_at = search_str.substr(from, to);
}

