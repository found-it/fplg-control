/*****************************************************
 *
 *  File:   vl6180.c
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 *****************************************************
 */
#include "../include/vl6180.h"

typedef union reg
{
    uint16_t name;
    uint8_t  byte[2];
} reg_t;

void hello()
{
    printf("Hello from %s!\n\n",__FILE__);
}


static int setup(const char *dev, int id)
{
    return SUCCESS;
}

static int read_data8(int fd, reg_t regi)
{
    return SUCCESS;
}


static int write_data8(int fd, reg_t regi, uint8_t data)
{
    return SUCCESS;
}

int vl6180_read_range(int fd)
{
    return SUCCESS;
}
