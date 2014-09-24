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

static DIRLISTINFO * 
list_directory(char ** params)
{
    char ** dirs_list = (char**)malloc(sizeof(char *) * 255);
    DIRLISTINFO * info = NULL;

    if(NULL == *(params + 0))
    {   
        char * dir = *(params + 1);
        DIR  * dir_pointer = NULL;
        struct dirent * dirs = NULL;
        if(NULL != dir)
        {
            if(NULL != (dir_pointer = opendir(dir)))
            {
                int i = 0;
                while(NULL != (dirs = readdir(dir_pointer)))
                {   
                    *(dirs_list + i ) = dirs->d_name;
                    i+= 1;
                }
                info = (DIRLISTINFO *)malloc(sizeof(DIRLISTINFO));
                info->size = i   ;
                info->list = dirs_list;
                return info;
            }
            else
            {
                printf("directory is incorrect");
            }
        }
    }
    return NULL;
}


static DIRLISTINFO *
reorder_string_list(DIRLISTINFO * info)
{
    SIZE size     = info->size;
    DIRLIST list  = info->list;
    for(int i = 0 ; i < size ; i++)
    {
        char * o_item = *(list + i);
        for(int n = 0 ; n < size - i ; n++)
        {   
            char * i_item = *(list + n);
            printf("%c : %c\n", *(list + i)[0], *(list + n)[0]);
            if(*(list + i)[0] > *(list + n)[0])
            {
                char * temp = *(list + i);
                *(list + i) = *(list + n);
                *(list + n) = temp;
            }
        }
    }
    return info;
}



void
ls_handler(int argc, char **argv)
{
    char ** cmds = parse_cmds(argc, argv);
    DIRLISTINFO *  info = list_directory(cmds);
    info = reorder_string_list(info);
    for(int i = 0 ;i < info->size; i++)
    {
        printf("%s\n", *(info->list + i));
    }
}
