#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

#define SIZE int
#define DIRLIST char **

#define CMD_LENGTH  10
#define DIR_COUNT 255

typedef struct DIRLISTINFO{
    
    SIZE size;
    DIRLIST list; 

} DIRLISTINFO;

void ls_handler(int argc, char ** argv);
