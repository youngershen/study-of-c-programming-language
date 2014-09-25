#include "ls.h"

char ** parse_cmds(int argc, char ** argv)
{
    char **ret = (char **)malloc(sizeof(char *) * CMD_LENGTH);

    if(2 == argc)
    {
        printf("%d\n", '-' == *(argv[1]));

        if('-' == *(argv[1]))
        {   
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
    else
    {
        char * cmd = NULL;
        char * dir = ".";
        *(ret + 0) = cmd;
        *(ret + 1) = dir;
        return ret;
    }

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
    else
    {
        exit(0);
    }
    return NULL;
}

static void test_sort(void)
{
    int a[10] = {1,2,1,2,3,42345,235,234,23,234};
    for(int i = 0 ; i < 10 ;i ++)
    {
        for(int n = 0 ; n < 10 - i; n++)
        {
            if(a[n + 1] > a[n])
            {
                a[n + 1] = a[n + 1] + a[n];
                a[n] = a[n + 1] - a[n];
                a[n + 1] = a[n + 1] - a[n];
            }
        }
    }
    for(int m = 0 ; m < 10; m++)
    {
        printf("%d\n", a[m]);
    }
}

static DIRLISTINFO *
reorder_string_list(DIRLISTINFO * info)
{
    SIZE size     = info->size;
    DIRLIST list  = info->list;

    for(int i = 0 ; i < size ; i++)
    {
        for(int n = 0 ; n > size - i ; n++)
        {  
            if(n < size - i - 1){
                if(*(list + n + 1)[0] >  *(list + n)[0])
                {
                    char * temp = *(list + n + 1);
                    *(list + n + 1) = *(list + n);
                    *(list + n) = temp;
                }
            }
        }
    }
    return info;
}

static 
bool get_file_stat(DIRLISTINFO * info)
{
    DIRLIST  list = info->list;
    SIZE size      = info->size;
    FILESTATS stats = (FILESTATS)malloc(sizeof(FILESTAT *) * size);    
    
    for(int i = 0 ; i < size ; i++)
    {
        char * path = *(info->list + i); 
        FILESTAT * astat = (FILESTAT * )malloc(sizeof(FILESTAT));
        int ret = stat(path, astat);
        if( 0 != ret )
        {
            printf("get file stat failed");
            return -1;
        }
        else
        {
            *(stats + i) = astat;
        }
    }
    info->file_stats = stats;
    return 0;
}

void
ls_handler(int argc, char **argv)
{
    char ** cmds = parse_cmds(argc, argv);
    DIRLISTINFO *  info = list_directory(cmds);
    //info = reorder_string_list(info);
    get_file_stat(info);
    for(int i = 0 ;i < info->size; i++)
    {
        printf("%s\n", *(info->list + i));
        FILESTAT * stat = *(info->file_stats + i);
        printf("%ld\n", stat->st_ctime);
    }

}
