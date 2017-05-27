#include <direct.h>
#include <dirent.h>
#include <tree.h>
#include <iostream>
#include <stdio.h>

using namespace std;

Tree::Tree() {}
Tree::~Tree() {}

bool Tree::is_eon_dir() {
    DIR *d = opendir("./eondata");
    bool exists = d != NULL ? true : false;
    closedir(d);
    return exists;
}

bool Tree::init() {
    mkdir("./eondata");
    mkdir("./eondata/config");
    mkdir("./eondata/data");
    mkdir("./eondata/projects");

    FILE *fp;
    fp = fopen("./eondata/projects/next_id.txt", "w");
    if (fp != NULL)
    {
        fputs("1", fp);
        fclose(fp);
        return true;
    }
    return false;
}
