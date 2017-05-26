#include <direct.h>
#include <dirent.h>
#include <tree.h>
#include <iostream>
#include <stdio.h>

using namespace std;

Tree::Tree() {}
Tree::~Tree() {}

bool Tree::is_timr_dir() {
    DIR *d = opendir("./timrdata");
    bool exists = d != NULL ? true : false;
    closedir(d);
    return exists;
}

bool Tree::init() {
    mkdir("./timrdata");
    mkdir("./timrdata/config");
    mkdir("./timrdata/data");
    mkdir("./timrdata/projects");

    FILE *fp;
    fp = fopen("./timrdata/projects/next_id.txt", "w");
    if (fp != NULL)
    {
        fputs("1", fp);
        fclose(fp);
        return true;
    }
    return false;
}
