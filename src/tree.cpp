#include <direct.h>
#include <dirent.h>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "date.h"
#include "project.h"
#include "tree.h"

using namespace std;

const char *const Tree::ROOT_DIR = "./eondata";
const char *const Tree::CONFIG_FILE = "./eondata/config.txt";
const char *const Tree::ENTRIES_DIR = "./eondata/entries";
const char *const Tree::ENTRIES_ID_FILE = "./eondata/entries/next_id.txt";
const char *const Tree::PROJECTS_DIR = "./eondata/projects";
const char *const Tree::PROJECTS_FILE = "./eondata/projects/projects.txt";
const char *const Tree::PROJECTS_ID_FILE = "./eondata/projects/next_id.txt";

const string Tree::MSG_ALREADY_INITIALIZED = "Directory is already an eon directory.";
const string Tree::MSG_ENTRIES_PROJECTS_DIR_FAILURE = "Could not create directories for entries and/or projects.";
const string Tree::MSG_INIT_FAILURE = "Could not create the required files.";
const string Tree::MSG_INIT_SUCCESS = "Created a new eon directory.";
const string Tree::MSG_ROOT_DIR_FAILURE = "Could not create eon root directory.";

Tree::Tree() {}
Tree::~Tree() {}

bool Tree::is_eon_dir() {
    DIR *d = opendir(ROOT_DIR);
    bool exists = d != NULL ? true : false;
    if (exists) closedir(d);
    return exists;
}

bool Tree::init(const string datetime, vector<string> &messages_human) {
    messages_human.clear();

    if (is_eon_dir())
    {
        messages_human.push_back(MSG_ALREADY_INITIALIZED);
        return false;
    }

    if (!create_dir(root_dir()))
    {
        messages_human.push_back(MSG_ROOT_DIR_FAILURE);
        return false;
    }

    if (mkdir(ENTRIES_DIR) + mkdir(PROJECTS_DIR) != 0)
    {
        messages_human.push_back(MSG_ENTRIES_PROJECTS_DIR_FAILURE);
        return false;
    }

    bool projects_id = create_file(PROJECTS_ID_FILE, "1");
    bool projects_file = create_file(PROJECTS_FILE, "");

    bool first_project = Project::add(Project::DEFAULT_PROJECT_NAME, datetime);

    bool entries_id = create_file(ENTRIES_ID_FILE, "1");

    // Must be re-calculated and upgraded when new configuration keys are added or existing ones changed
    int initial_config_length = 30;
    char config_str[initial_config_length];
    initial_config_str(datetime.substr(0, 11), config_str);
    bool config = create_file(CONFIG_FILE, config_str);

    if (projects_id && projects_file && first_project && entries_id && config)
    {
        messages_human.push_back(MSG_INIT_SUCCESS);
        return true;
    }
    else
    {
        messages_human.push_back(MSG_INIT_FAILURE);
        return false;
    }
}

bool Tree::create_dir(const char path[])
{
    if (mkdir(path) != 0)
    {
        return false;
    }
    return true;
}

void Tree::initial_config_str(const string dte, char return_str[])
{
    sprintf(return_str, "date=%s\nproject_id=1\n", dte.c_str());
}

bool Tree::create_file(const char path[], const char data[]) {
    FILE *fp;
    fp = fopen(path, "w");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
        return true;
    }
    return false;
}

void Tree::ensure_year_dir(const string year)
{
    string path = string(ENTRIES_DIR) + "/" + year;
    DIR *d = opendir(path.c_str());
    if (d == NULL)
    {
        mkdir(path.c_str());
    }
    else
    {
        closedir(d);
    }
}

const char *Tree::root_dir()
{
    return ROOT_DIR;
}
