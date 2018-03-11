/**
 *  \file   vl6180.h
 *  \author James Petersen <jpetersenames@gmail.com>
 */

#ifndef VL6180_H
#define VL6180_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>


/* Defines */
#define VL6180_DEV "/dev/i2c-1"
#define VL6180_ID  0x29

/**
    vl6180_setup

    \brief  This function sets up the vl6180, sends it all
            the configuration commands that are given in the
            datasheet.

    \return A pointer to a fully set up i2c_dev struct.
 */
struct i2c_device *vl6180_setup();


/**
    vl6180_read_range

    \brief  This function reads the range in mm.

    \return The range as a one byte value.
  */
uint8_t vl6180_read_range(struct i2c_device *self);

#endif
