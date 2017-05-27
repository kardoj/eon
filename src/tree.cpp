#include <direct.h>
#include <dirent.h>
#include <tree.h>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

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

    bool projects_id = create_file("./eondata/projects/next_id.txt", "2");

    string datetime = string(dte) + "_" + string(tme);
    bool first_project = create_file("./eondata/projects/projects.txt", "1 general " + datetime + " " + datetime, true);

    bool entries_id = create_file("./eondata/entries/next_id.txt", "1");
    bool config = create_file("./eondata/config.txt", initial_config_string(dte));

    return projects_id && first_project && entries_id && config;
}

string Tree::initial_config_string(char dte[])
{
    return "date=" + string(dte) + "\nproject=1";
}

bool Tree::create_file(string path, string data, bool add_nl/*=false*/) {
    FILE *fp;
    fp = fopen(path.c_str(), "w");
    if (fp != NULL)
    {
        fputs(data.c_str(), fp);
        if (add_nl) fputs("\n", fp);
        fclose(fp);
        return true;
    }
    return false;
}
