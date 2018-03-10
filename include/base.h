/*
 *  File:   base.h
 *  Author: James Petersen <jpetersenames@gmail.com>
 */

#ifndef BASE_H
#define BASE_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Defines */
#define SUCCESS 0
#define ERROR  -1
#define EXIT    1

/**
    This structure holds all the necessary information
    for an I2C device.

    It is used for the VL6180 and the TMP007.
 */
struct i2c_device
{
    int       fd;
    int       addr;
    char     *dev;
    uint8_t (*read)();
};

#endif
