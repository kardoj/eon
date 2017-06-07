## Eon

Eon is a command line tool for task time management and statistics. Data is saved in the filesystem. Eon is inspired by git command line tool.

### Usage
`eon init` creates a new eon directory in the current directory. Eon will create a directory called `eondata` which will contain all its files.

`eon addproject "eon"` - adds a new project identificator eon that can be used for entries. Every entry must have a reference to a project. A default project named "General" is created automatically on `eon init`. It is also set as an active project.

`eon set -d/--date 2017-12-12 -p/--project <project_id>` - sets the date and project so that they are not be required on every new entry.

`eon projects` - lists all available projects and shows the currently active one.

### In the making
`eon add 12 14 "Improving stability"` - creates a new entry in `eondata/data/2017/5.txt` using the date and project from the configuration file.

`eon add 25.05.2017 "eon" 22.30 23.30 "Improving stability"` - creates a new entry similarly to the previous command but uses the supplied date and project.

#### Backlog
* mktime() ingores wrong date? (date verifier)
* Allow project name for `eon set -p/--project <project_name>`.