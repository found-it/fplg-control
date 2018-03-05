/*****************************************************
 *
 *  File:   vl6180.h
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 *****************************************************
 */

#ifndef VL6180_H
#define VL6180_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "base.h"
#include "logging.h"

#define VL6180_DEV "/dev/i2c-1"
#define VL6180_ID  0x29


//int vl6180_setup(const char *dev, int id);
int vl6180_setup();
uint8_t vl6180_read_range(int fd);

#endif
