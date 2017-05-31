## Eon

Eon is a command line tool for task time management and statistics. Data is saved in the filesystem. Eon is inspired by git command line tool.

### Usage
`eon init` creates a new eon directory in the current directory. Eon will create a directory called `eondata` which will contain all its files.

`eon addproject "eon"` - will add a new project identificator eon that can be used for entries. Every entry must have a reference to a project. A default project named "General" will be created automatically on `eon init`. It is also set as an active project.

`eon set -d/--date 25.05.2017 -p/--project "eon"` - will set the date and project so that they will not be required on every new entry.

### In the making
`eon add 12 14 "Improving stability"` - will create a new entry in `eondata/data/2017/5.txt` assuming that the configuration command shown on the previous line was run beforehand.

`eon add 25.05.2017 "eon" 22.30 23.30 "Improving stability"` - will create an entry similar to the previous command but does not require date and project set beforehand.

#### Backlog
* Date parser and check when setting a new date (configuration)