#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

#define SIZE int
#define DIRLIST char **

#define CMD_LENGTH  10
#define DIR_COUNT 255
#define FILESTAT struct stat
#define FILESTATS FILESTAT **

typedef struct DIRLISTINFO{
    
    SIZE size;
    DIRLIST list;
    FILESTATS file_stats;

} DIRLISTINFO;

void ls_handler(int argc, char ** argv);
