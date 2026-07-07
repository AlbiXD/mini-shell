#include "../include/shell.h"

const char *shell = "shell$ ";
const char *user_bin = "/usr/bin/";
#define BUFSIZE 1024

int SHL_BuildPath(char *buf, char *PATH)
{

    char ch = 0;

    if (buf[0] != '.' && buf[0] != '/')
    {
        // usr/bin file
        int idx = 9;

        for (int i = 0; i < 9; i++)
            PATH[i] = user_bin[i];

        int i = 0;
        while ((ch = buf[i++]) != '\0')
            PATH[idx++] = ch;

        PATH[idx] = 0;
        return 0;
    }
    else
    {
        // cwd
        // other directory
        int i = 0;
        while ((ch = buf[i]) != '\0')

            PATH[i++] = ch;

        PATH[i] = '\0';

        return SHELL_CMD_INTERNAL;
    }
}

char **SHL_BuildArgs(char *buf, int size)
{
    int total_strings = STR_Count(buf, size);

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
int SHL_Execute(char *path, char **args)
{
    int fd = 0;
    if ((fd = FILE_Check(path)) < 0)
        return -1;

    int status = 0;
    int pid = fork();
    // Child stuff
    if (pid != 0)
        wait(&status);
    else
    {
        execv(path, args);
        exit(0);
    }
    return status;
}

int SHL_Read(char *buf)
{
    int w = 0, r = 0;
    if ((w = write(1, shell, 7)) < 0) // Writing shell symbol
        return SHELL_INPUT_ERROR;

    if ((r = read(0, buf, BUFSIZE)) < 0) // Reading user input
        return SHELL_INPUT_ERROR;

    if (STR_Tokanize(buf, r) < 0) // Tokanizing Input
        return SHELL_INPUT_ERROR;

    return r;
}
int SHL_Shell()
{
    char cwd[BUFSIZE];
    if (getcwd(cwd, BUFSIZE) == NULL)
        return -1; // Get current directory

    while (1)
    {
        char buf[1024], bin[1024];
        int r = 0;

        if ((r = SHL_Read(buf)) < 0)
            continue;

        SHL_BuildPath(buf, bin);

        char **args = SHL_BuildArgs(buf, r);
        SHL_Execute(bin, args);

        free(args);
    }
}