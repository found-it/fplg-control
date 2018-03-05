/*****************************************************
 *
 *  File:   base.h
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 *****************************************************
 */

#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SUCCESS 0
#define ERROR  -1
#define EXIT    1

typedef struct i2c_dev
{
    int      fd;
    int      addr;
    char    *dev;
    uint8_t (*read)(int);
    void    (*setup)();
}i2c_dev_t;

#endif
