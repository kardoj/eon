## Timr

Timr is a command line tool for task time management and statistics. Data is saved in the filesystem. Timr is inspired by git command line tool.

### Usage
`timr init` creates a new timr directory in the current directory. Timr will create a directory called `timrdata` which will contain all its files.

### In the making
`timr addproject "timr"` - will add a new project named timr that can be used as a project for tasks.

`timr set -d/--date 25.05.2017 -p/--project "timr"` - will set the date and project so that they will not be required on every new entry.

`timr add 12 14 "Improving stability"` - will create a new entry in `timrdata/data/2017/5.txt` assuming that the configuration command shown on the previous line was run beforehand.

`timr add 25.05.2017 "timr" 22.30 23.30 "Improving stability"` - will create an entry similar to the previous command but does not require date and project set beforehand.