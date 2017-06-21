#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "cruditem.h"

using namespace std;

CrudItem::CrudItem() {}
CrudItem::~CrudItem() {}

string CrudItem::get_next_id_and_increment(const string path)
{
    char id[MAX_ID_LENGTH];
    char next_id[MAX_ID_LENGTH];

    FILE *fp = fopen(path.c_str(), "r+");
    if (fp != NULL)
    {
        fgets(id, MAX_ID_LENGTH, fp);
        sprintf(next_id, "%d", atoi(id) + 1);
        rewind(fp);
        fputs(next_id, fp);
        fclose(fp);
        return string(id);
    }
    else
    {
        return string("-1");
    }
}
