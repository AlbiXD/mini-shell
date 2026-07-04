#include "../include/strings.h"
#include <stdio.h>
int STR_Count(char *buf, int r)
{
    int total_strings = 0;
    for (int i = 0; i < r; i++)
        if (buf[i] == 0)
            total_strings++;

    return total_strings;
}

int STR_Size(char *buf)
{
    int strsize = 0;
    int i = 0;

    while (buf[i++] != '\0')
        strsize++;

    return strsize;
}
int STR_Tokanize(char *buf, int size)
{
    if (buf == NULL)
        return -1;

    if (size <= 0)
        return -1;

    for (int i = 0; i < size; i++)
        if (buf[i] == '\n' || buf[i] == ' ')
            buf[i] = 0;

    return 0;
}