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


int setup(const char *dev, int id)
{
    int fd;
    int ready = 0;

    /* 
     *   open up the device 
     */
    if ((fd = open(dev, O_RDWR)) < 0)
    {
        LOG_ERROR_S("Opening VL6180\n");
        return ERROR;
    }
    else
        LOG_DEBUG_S("VL6180 Opened Successfully\n");
    
    /*
     *   initialize the device as a slave
     */
    if (ioctl(fd, I2C_SLAVE, id) < 0)
    {
        LOG_ERROR_S("Initializing Communication with VL6180\n");
        return ERROR;
    }
    else
        LOG_DEBUG_S("VL6180 Communication Initialized\n");
    return fd;
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
