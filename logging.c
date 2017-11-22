/***************************************************
 *
 *  File:   logging.c
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 ***************************************************
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "logging.h"

void logr(char *fmt, ...)
{
    printf("In: logr()\n");
    char *str;
    int len;
    va_list cpy;
    va_list args;

    if (!fmt)
        fmt = "";

    va_start(args, fmt);
    len = vsnprintf(NULL, 0, fmt, args);
    printf("len: %d\n", len);
    va_end(args);

    str = malloc(len+1);
    va_start(args, fmt);
    vsnprintf(str, len+1, fmt, args);
    va_end(args);

    printf("%s\n", str);
    free(str);
}
