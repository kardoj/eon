#include <direct.h>
#include <dirent.h>
#include <tree.h>
#include <iostream>
#include <stdio.h>

Tree::Tree() {}
Tree::~Tree() {}

bool Tree::is_eon_dir() {
    DIR *d = opendir("./eondata");
    bool exists = d != NULL ? true : false;
    closedir(d);
    return exists;
}

bool Tree::init(char dte[], char tme[]) {
    mkdir("./eondata");
    mkdir("./eondata/entries");
    mkdir("./eondata/projects");

    bool projects_id = create_file((char*) "./eondata/projects/next_id.txt", (char*) "2");

    char project_data[65];
    sprintf(project_data, "1 \"general\" \"%s %s\" \"%s %s\"\n", dte, tme, dte, tme);
    bool first_project = create_file((char*) "./eondata/projects/projects.txt", project_data);

    bool entries_id = create_file((char*) "./eondata/entries/next_id.txt", (char*) "1");

    // Must be re-calculated and upgraded when new configuration keys are added or existing ones changed
    int initial_config_length = 26;
    char config_str[initial_config_length];
    initial_config_str(dte, config_str);
    bool config = create_file((char*) "./eondata/config.txt", config_str);

    return projects_id && first_project && entries_id && config;
}

void Tree::initial_config_str(char dte[], char *return_str)
{
    sprintf(return_str, "date=%s\nproject=1", dte);
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
