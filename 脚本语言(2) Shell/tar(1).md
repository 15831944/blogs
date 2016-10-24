# synopsis

     tar  Acdrtux --get [options] [pathname ...]

# Function Letters

Main operation mode:

| short | long                      | meaning                                          |
| ----- | ------------------------- | ------------------------------------------------ |
| -A    | --catenate, --concatenate | append tar files to an archive                   |
| -c    | --create                  | create a new archive                             |
| -d    | --diff, --compare         | find differences between archive and file system |
|       | --delete                  | delete from the archive (not on mag tapes!)      |
| -r    | --append                  | append files to the end of an archive            |
| -t    | --list                    | list the contents of an archive                  |
|       | --test-label              | test the archive volume label and exit           |
| -u    | --update                  | only append files newer than copy in archive     |
| -x    | --extract, --get          | extract files from an archive                    |

# Other Options

Operation modifiers:

# environment

The behavior of tar is controlled by the following environment variables, among others:

SIMPLE_BACKUP_SUFFIX
TAR_OPTIONS
TAPE
TAR_LONGLINK_100
