#include "ls.h"

char ** parse_cmds(int argc, char ** argv)
{
    char **ret = (char **)malloc(sizeof(char *) * CMD_LENGTH);

    if(2 == argc)
    {
        if('-' == *(argv[1]))
        {   
            printf("2 prms");
            char * cmd = argv[1];
            char * dir = ".";
            *(ret + 0) = cmd;
            *(ret + 1) = dir;
            return ret;
        }
        else
        {
            char * cmd = NULL;
            char * dir = argv[1];
            *(ret + 0) = cmd;
            *(ret + 1) = dir;
            return ret;
        }
    }
    if(3 == argc)
    {
        if('-' == *(argv[1]))
        {
            char * cmd = argv[1];
            char * dir = argv[2];
            *(ret + 0)  = cmd;
            *(ret + 1)  =  dir;
            return ret;
        }
        else
        {
            printf("wrong commands %s, %s", argv[1], argv[2]);
            exit(0);
        }
    }

    printf("wrong commands ");
    exit(0);
}
