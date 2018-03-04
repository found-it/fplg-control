/*****************************************************
 *
 *  File:   lpec.c
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 *****************************************************
 */

#include "../include/lpec.h"
#include <stdio.h>

int main()
{
    printf("\n\n");

    LOG_ERROR("this is an error: %d\n", 123);
    printf("\n");
    LOG_DEBUG("this is an debug: %d\n", 123);
    printf("\n");
    LOG_WARN("this is an warn: %d\n", 123);
    printf("\n");
    LOG_INFO("this is an info: %d\n", 123);

    printf("\n\n\n");

    hello();
    int vl_fd = setup(DEVICE, DEFAULT_ID);

    return 0;
}
