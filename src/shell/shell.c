#include "../include/shell.h"

const char *shell = "shell$ ";
const char *path = "/usr/bin/";

int SHL_BuildPath(char *buf, char *PATH)
{
    int idx = 9;
    char ch = 0;

    int i;
    for (i = 0; i < 9; i++)
        PATH[i] = path[i];

    i = 0;
    while ((ch = buf[i++]) != '\0')
        PATH[idx++] = ch;

    PATH[idx] = 0;

    return 0;
}

char **SHL_BuildArgs(int total_strings, char *buf)
{
    char **args = malloc(sizeof(char *) * total_strings + 1);
    char *ptr = buf;

    for (int i = 0; i < total_strings; i++)
    {
        int strsize = STR_Size(ptr);

        args[i] = ptr;

        ptr += strsize + 1;
    }

    args[total_strings] = NULL;

    return args;
}
int SHL_Execute(char *PATH, char **args)
{
    int status = 0;
    int pid = fork();
    // Child stuff
    if (pid != 0)
        wait(&status);
    else
    {
        execv(PATH, args);
        exit(0);
    }
    return status;
}
int SHL_Shell()
{
    while (1)
    {
        char buf[1024], PATH[1024];
        int r = 0, w = 0;

        if ((w = write(1, shell, 7)) < 0) // Writing shell symbol
            continue;
        if ((r = read(0, buf, sizeof(buf))) < 0) // Reading user input
            continue;

        if (STR_Tokanize(buf, r) < 0) // Tokanizing Input
            return SHELL_INPUT_ERROR;

        // Will build the path
        SHL_BuildPath(buf, PATH);

        int fd = 0;
        if ((fd = FILE_Check(PATH)) < 0)
            continue;

        int total_strings = STR_Count(buf, r);
        char **args = SHL_BuildArgs(total_strings, buf);

        int status = SHL_Execute(PATH, args);

        free(args);
    }
}