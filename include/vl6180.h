/*****************************************************
 *
 *  File:   vl6180.h
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 *****************************************************
 */
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

#define DEVICE     "/dev/i2c-1"
#define DEFAULT_ID 0x29


void hello();
int setup(const char *dev, int id);
int vl6180_read_range(int fd);

