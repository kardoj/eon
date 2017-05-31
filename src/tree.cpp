#include <direct.h>
#include <dirent.h>
#include <iostream>
#include <stdio.h>

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
    closedir(d);
    return exists;
}

bool Tree::init(char dte[], char tme[]) {
    mkdir(ROOT_DIR);
    mkdir(ENTRIES_DIR);
    mkdir(PROJECTS_DIR);

    bool projects_id = create_file((char*) PROJECTS_ID_FILE, (char*) "1");
    bool projects_file = create_file((char*) PROJECTS_FILE, (char*) "");
    bool first_project = Project::add((char*) Project::DEFAULT_PROJECT_NAME, dte, tme);

    bool entries_id = create_file((char*) ENTRIES_ID_FILE, (char*) "1");

    // Must be re-calculated and upgraded when new configuration keys are added or existing ones changed
    int initial_config_length = 30;
    char config_str[initial_config_length];
    initial_config_str(dte, config_str);
    bool config = create_file((char*) CONFIG_FILE, config_str);

    return projects_id && projects_file && first_project && entries_id && config;
}

void Tree::initial_config_str(char dte[], char *return_str)
{
    sprintf(return_str, "date=%s\nproject_id=1", dte);
}

bool Tree::create_file(char path[], char data[]) {
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
