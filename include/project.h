#ifndef PROJECT_H
#define PROJECT_H

class Project
{
    public:
        const static char *DEFAULT_PROJECT_NAME;
        const static int MAX_PROJECT_ROW_LENGTH = 300;

        Project();
        virtual ~Project();
        static bool add(char name[], char dte[], char tme[]);
        static bool exists(int project_id);

    protected:

    private:
};

#endif // PROJECT_H
