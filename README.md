## Eon

Eon is a command line tool for task time management and statistics. Data is saved in the filesystem. Eon is inspired by git command line tool.

### Usage
`eon init` creates a new eon directory in the current directory. Eon will create a directory called `eondata` which will contain all its files.

`eon addproject <project_name|"multi word project name">` - adds a new project identificator that can be used for entries. Every entry must have a reference to a project. A default project named "General" is created automatically on `eon init`. It is also set as an active project.

`eon set -d/--date <YYYY-M(M)-D(D)|D(D).M(M).YYYY> -p/--project <project_id>` - sets the active date and project in the configuration for `add` command.

`eon projects` - lists all available projects and shows the currently active one.

### In the making
`eon add 12 14 "Improving stability"` - creates a new entry in `eondata/data/2017/5.txt` using the date and project from the configuration file.

`eon add 25.05.2017 "eon" 22.30 23.30 "Improving stability"` - creates a new entry similarly to the previous command but uses the supplied date and project.

#### Backlog
* Allow project name for `eon set -p/--project <project_name>`.