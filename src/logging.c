/*
 *  File:   logging.c
 *  Author: James Petersen <jpetersenames@gmail.com>
 */

#include "../include/logging.h"

void logr(char *fmt, ...)
{
    char *str;
    int len;
    va_list args;

    if (!fmt)
        fmt = "";

    va_start(args, fmt);
    len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    str = malloc(len+1);
    va_start(args, fmt);
    vsnprintf(str, len+1, fmt, args);
    va_end(args);

    printf("%s\n", str);
    free(str);
}
