#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#define CMD_LENGTH  10

char ** parse_cmds(int argc, char ** argv);

void ls_directory(char * dir, char * cmds);
