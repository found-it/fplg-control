/*
 *  File:   tmp007.h
 *  Author: James Petersen <jpetersenames@gmail.com>
 */

#ifndef TMP007_H
#define TMP007_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define TMP007_DEV "/dev/i2c-1"
#define TMP007_ID  0x40

#define SUCCESS 0
#define ERROR  -1
#define EXIT    1

#define SENSOR_VOLTAGE_REGISTER 0x00
#define LOCAL_TEMP_REGISTER     0x01
#define CONFIGURATION_REGISTER  0x02
#define OBJECT_TEMP_REGISTER    0x03
#define STATUS_REGISTER         0x04


struct i2c_device *tmp007_setup();
float tmp007_read_temp(struct i2c_device *self);
//union return_data tmp007_read_temp(struct i2c_device *self);


#endif
