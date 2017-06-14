#include <direct.h>
#include <dirent.h>
#include <iostream>
#include <stdio.h>

#include "date.h"
#include "project.h"
#include "tree.h"

const char *Tree::ROOT_DIR = "./eondata";
const char *Tree::CONFIG_FILE = "./eondata/config.txt";
const char *Tree::ENTRIES_DIR = "./eondata/entries";
const char *Tree::ENTRIES_ID_FILE = "./eondata/entries/next_id.txt";
const char *Tree::PROJECTS_DIR = "./eondata/projects";
const char *Tree::PROJECTS_FILE = "./eondata/projects/projects.txt";
const char *Tree::PROJECTS_ID_FILE = "./eondata/projects/next_id.txt";

Tree::Tree() {}
Tree::~Tree() {}

bool Tree::is_eon_dir() {
    DIR *d = opendir(ROOT_DIR);
    bool exists = d != NULL ? true : false;
    if (exists) closedir(d);
    return exists;
}

bool Tree::init() {
    mkdir(ROOT_DIR);
    mkdir(ENTRIES_DIR);
    mkdir(PROJECTS_DIR);

    bool projects_id = create_file(PROJECTS_ID_FILE, "1");
    bool projects_file = create_file(PROJECTS_FILE, "");

    bool first_project = Project::add(Project::DEFAULT_PROJECT_NAME);

    bool entries_id = create_file(ENTRIES_ID_FILE, "1");

    // Must be re-calculated and upgraded when new configuration keys are added or existing ones changed
    int initial_config_length = 30;
    char config_str[initial_config_length];
    initial_config_str(Date::current_date(), config_str);
    bool config = create_file(CONFIG_FILE, config_str);

    return projects_id && projects_file && first_project && entries_id && config;
}

void Tree::initial_config_str(const string dte, char *return_str)
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
