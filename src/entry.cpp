#include <cstdio>
#include <iostream>
#include "date.h"
#include "entry.h"
#include "period.h"
#include "project.h"
#include "tree.h"

using namespace std;

Entry::Entry() {}
Entry::~Entry() {}

bool Entry::add(
    const string dte,
    const string project_id_or_name,
    const string start_time,
    const string end_time,
    const string description)
{
    Period period = Period(start_time, end_time);

    if (!period.is_valid())
    {
        cout << "Invalid time period entered. Nothing to do." << endl;
        return false;
    }

    Date d = Date(dte);

    if (!d.is_valid())
    {
        cout << "Invalid date entered. Nothing to do." << endl;
        return false;
    }

    int p_id;
    char project_id[MAX_ID_LENGTH];

    if (Project::exists(project_id_or_name, p_id))
    {
        sprintf(project_id, "%d", p_id);
    }
    else
    {
        cout << "Project with id or name \"" << project_id_or_name << "\" does not exist. Nothing to do." << endl;
        return false;
    }

    int y = d.get_year();
    int m = d.get_month();
    int wdy = d.get_wday();

    char year[5], month[3], wday[2];
    sprintf(year, "%d", y);
    sprintf(month, "%d", m);
    sprintf(wday, "%d", wdy);

    string year_str = string(year);

    Tree::ensure_year_dir(year_str);

    string datetime = Date::current_date_with_time();
    string path = string(Tree::ENTRIES_DIR) + "/" + year_str + "/" + string(month) + ".txt";

    FILE *fp = fopen(path.c_str(), "a");

    if (fp != NULL)
    {
        string id = get_next_id_and_increment(Tree::ENTRIES_ID_FILE,
                                              string("There was a problem opening entries id file. Nothing to do."));
        if (id.compare("-1") == 0) return false;

        char minutes[MAX_MINUTES_LENGTH];
        sprintf(minutes, "%d", period.minutes());
        string entry =
            id + " " +
            dte + " " +
            wday + " " +
            string(project_id) + " " +
            start_time + " " +
            end_time + " " +
            string(minutes) + " " +
            "\"" + description + "\" " +
            datetime + " " +
            datetime + "\n";
        fputs(entry.c_str(), fp);
        fclose(fp);
        return true;
    }
    else
    {
        cout << "Something went wrong while opening the entry file." << endl;
        return false;
    }
}

string Entry::get_next_id_and_increment(const string path, const string file_open_error)
{
    return CrudItem::get_next_id_and_increment(path, file_open_error);
}
