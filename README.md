## Eon

Eon is a command line tool for task time management and statistics. Data is saved in the filesystem. Eon is inspired by git command line tool.

The project is at a very early stage at the moment and is suitable for testing only. I'd like to think that the file structure and content format are mostly in place but most everything is still subject to rapid change.

### Usage
`eon init` creates a new eon directory in the current directory. Eon will create a directory called `eondata` which will contain all its files.


`eon set -d/--date <YYYY-M(M)-D(D)|D(D).M(M).YYYY>` - sets the active date in the configuration for `add` command.

`eon set -p/--project <project_id|project_name|"multi word project name">` - sets the active project in the configuration for `add` command.

Both the -p/--project and -d/--date can also be set with one `set` command. Order of the keys is not important.

`eon addproject <project_name|"multi word project name">` - adds a new project identificator that can be used for entries. Every entry must have a reference to a project. A default project named "General" is created automatically on `eon init`. It is also set as an active project.

`eon projects` - lists all available projects and shows the currently active one.

`eon date` - shows the currently set date.

`eon add 12 14 "Improving stability"` - creates a new entry in `eondata/entries/<year>/<month>.txt` using the date and project from the configuration file.

`eon add 25.05.2017 "eon" 22.30 23.30 "Improving stability"` - creates a new entry similarly to the shorter `add` command but uses the supplied date and project.

### In the making

Figuring out a testing solution and testing everything that has been implemented so far.

`eon updateproject <project_id|project_name|"multi word project name"> <new_name>` - Updates project name.

Tracking project usage. Additional column with usage count for project which is updated accordingly when adding a new entry or removing an existing one.

`eon deleteproject <project_id|project_name|"multi word project name">` - Deletes the project if the project is not in use.