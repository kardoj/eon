#include <direct.h>
#include <dirent.h>
#include <iostream>
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
    if (mkdir(entries_dir()) + mkdir(projects_dir()) != 0)
    {
        messages_human.push_back(MSG_ENTRIES_PROJECTS_DIR_FAILURE);
        return false;
    }
    if (!create_file(projects_file(), ""))
    {
        messages_human.push_back(MSG_INIT_FAILURE);
        return false;
    }
    if (!add_default_project(datetime))
    {
        messages_human.push_back(MSG_INIT_FAILURE);
        return false;
    }
    if (!create_file(entries_id_file(), "1"))
    {
        messages_human.push_back(MSG_INIT_FAILURE);
        return false;
    }
    char config_str[INITIAL_CONFIG_LENGTH];
    initial_config_str(datetime.substr(0, 10), config_str);
    if (!create_file(config_file(), config_str))
    {
        messages_human.push_back(MSG_INIT_FAILURE);
        return false;
    }
    messages_human.push_back(MSG_INIT_SUCCESS);
    return true;
}

bool Tree::add_default_project(const string datetime)
{
    // Ignoring possbile errors here because this method is private
    // and is called on init which means it should not fail
    // TODO: can be thought about later
    vector<string> messages_human;
    return Project().add(Project::DEFAULT_PROJECT_NAME, datetime, messages_human);
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

const char *Tree::config_file()
{
    return CONFIG_FILE;
}

const char *Tree::entries_dir()
{
    return ENTRIES_DIR;
}

const char *Tree::entries_id_file()
{
    return ENTRIES_ID_FILE;
}

const char *Tree::projects_dir()
{
    return PROJECTS_DIR;
}

const char *Tree::projects_file()
{
    return PROJECTS_FILE;
}

const char *Tree::root_dir()
{
    return ROOT_DIR;
}
