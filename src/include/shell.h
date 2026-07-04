#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "strings.h"
#include "file.h"

extern const char *shell;
extern const char *path;

typedef enum shell_return_t
{
    SHELL_INPUT_ERROR = -1,
    SHELL_FILE_ERROR = -2
} shell_return_t;
char **SHL_BuildArgs(int total_strings, char *buf);
int SHL_BuildPath(char *buf, char *PATH);
int SHL_Read(char *buf);
int SHL_Shell();

#endif