#include <cstdio>
#include <iostream>
#include <vector>
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
    vector<string> messages_human;

    if (Project::exists(project_id_or_name, p_id, messages_human))
    {
        sprintf(project_id, "%d", p_id);
    }
    else
    {
        if (messages_human.size() >= 1)
        {
            cout << messages_human.at(0) << endl;
        }
        return false;
    }

    char year[5], month[3], wday[2];
    sprintf(year, "%d", d.get_year());
    sprintf(month, "%02d", d.get_month());
    sprintf(wday, "%d", d.get_wday());

    string year_str = string(year);

    Tree::ensure_year_dir(year_str);

    string created_at = Date::current_date_with_time();
    string path = string(Tree::ENTRIES_DIR) + "/" + year_str + "/" + string(month) + ".txt";

    FILE *fp = fopen(path.c_str(), "a+");

    if (fp != NULL)
    {
        string id = build_id(year, month, get_nr_from_last_row_and_move_pointer_to_the_end(fp));

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
            created_at + " " +
            created_at + "\n";
        fputs(entry.c_str(), fp);
        fclose(fp);
        return true;
    }
    else
    {
        cout << "Could not open the entries file. Nothing to do." << endl;
        return false;
    }
}

string Entry::get_nr_from_last_row_and_move_pointer_to_the_end(FILE *fp)
{
    char row[MAX_ENTRY_ROW_LENGTH] = { "0" };
    while (!feof(fp))
    {
        if (fgets(row, MAX_ENTRY_ROW_LENGTH, fp) == NULL) break;
    }

    string row_str = string(row);
    if (row_str.compare("0") == 0)
    {
        return row_str;
    }
    else
    {
        int split_pos = row_str.find_first_of(" ");
        return row_str.substr(6, split_pos);
    }
}

string Entry::build_id(const string year, const string month, const string previous_nr)
{
    int current_nr = atoi(previous_nr.c_str());
    char current_nr_ch[previous_nr.size() + 1];
    sprintf(current_nr_ch, "%d", current_nr + 1);
    return year + month + string(current_nr_ch);
}
