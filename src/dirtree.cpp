#include <direct.h>
#include <dirent.h>
#include "dirtree.h"
#include <iostream>

using namespace std;

DirTree::DirTree() {}
DirTree::~DirTree() {}

bool DirTree::is_timr_dir() {
    DIR *d = opendir("./timrdata");
    bool exists = d != NULL ? true : false;
    closedir(d);
    return exists;
}

void DirTree::init() {
    mkdir("./timrdata");
    mkdir("./timrdata/config");
    mkdir("./timrdata/data");
}
