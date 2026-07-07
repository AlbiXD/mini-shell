#include "../include/file.h"
#include "../include/shell.h"

int FILE_Check(char const *path)
{
    int fd = open(path, O_RDONLY);
    
    if (fd == -1)
    {
        if (errno == ENOENT)
            printf("command not found\n");
        else
        {
            if (errno == EACCES)
                printf("Permission denied\n");
            else
                printf("Error\n");
        }
        return SHELL_FILE_ERROR;
    }

    return fd;
}