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

static DIRLISTINFO *
sort_dir_by_length(DIRLISTINFO * info)
{
    SIZE size = info->size;
    DIRLIST list = info->list;
    
    char * ** p_dirlist = (char * **)malloc(sizeof(DIRLIST) * size);

    char  flag = *(list + 0)[0];
    int count = 0;
    int p_dir_count = 0;
    char ** dir_buffer = (char **)malloc(sizeof(char *) * size);
    
    int sort_dir_count[size][size];
    for(int i = 0 ; i < size; i ++)
    {

        if(flag ==*(list + i)[0])
        {
           *(dir_buffer + count) = *(list + i);
           count ++;
        }
        else
        {   sort_dir_count[p_dir_count][0] = count; 
            *(p_dirlist + p_dir_count) = dir_buffer;
            count = 0 ;
            p_dir_count += 1;
            flag = *(list + i)[0];
            dir_buffer = (char **)malloc(sizeof(char *) *size);
            *(dir_buffer + count) = *(list + i);
            count ++ ;
        }
    }

    for(int n = 0 ; n < p_dir_count + 1 ; n ++)
    {
        for(int m = 0 ; m < sort_dir_count[n][0] ; m ++)
        {
            for(int k = 0 ; k < sort_dir_count[n][0] - m ; k++)
            {
                int dir_len      = strlen( *(*(p_dirlist + n) + k) );
                int next_dir_len = strlen( *(*(p_dirlist + n) + k + 1));
                if(dir_len > next_dir_len)
                {
                    char * temp;
                    temp = *(*(p_dirlist + n) + k);
                    *(*(p_dirlist + n) + k) = *(*(p_dirlist + n) + k + 1);
                    *(*(p_dirlist + n) + k + 1) = temp;
                }
            }
        }
    }
    
    DIRLIST new_list = (DIRLIST)malloc(sizeof(char *) * size);
    for(int i = 0 ; i < p_dir_count; i ++)
    {
        for(int n = 0; n < sort_dir_count[i][0]; n++)
        {
            int off_set = 0;
            for(int m = 0 ; m < i ; m ++)
            {
                off_set += sort_dir_count[i + m][0];
                off_set += n;
            }
            *(new_list + off_set) = *(*(p_dirlist + i) + n);
        }
    }
    info->list = new_list;
    return info;
}


static DIRLISTINFO *
reorder_string_list(DIRLISTINFO * info)
{
    SIZE size     = info->size;
    DIRLIST list  = info->list;

    for(int i = 0 ; i < size ; i++)
    {
        for(int n = 0 ; n < size - i ; n++)
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

    //info =  sort_dir_by_length(info);
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
    info = reorder_string_list(info);
    get_file_stat(info);
    for(int i = 0 ;i < info->size; i++)
    {
        printf("%s\n", *(info->list + i));
        FILESTAT * stat = *(info->file_stats + i);
        //printf("%ld\n", stat->st_ctime);
    }

}
