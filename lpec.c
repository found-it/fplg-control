/***************************************************
 *
 *  File:   lpec.c
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 ***************************************************
 */

#include "lpec.h"
#include <stdio.h>

int main()
{
    printf("\n\n");

    LOG_ERROR("this is an error: %d\n", 111);
    PERR("this is also err%d\n",22);

    return 0;
}
