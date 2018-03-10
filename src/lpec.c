/*
 *  File:   lpec.c
 *  Author: James Petersen <jpetersenames@gmail.com>
 */

#include "../include/lpec.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    printf(GREEN "Welcome to the Linear Power Electronic Controller\n\n" RESET);

#if 0
    int vl_fd = setup(DEVICE, DEFAULT_ID);
    int range = 0;
    for (int i = 0; i < 63; ++i)
        range += vl6180_read_range(vl_fd);
    printf("range: %dmm\n", range>>6);
#endif

    /* vl6180 */
    LOG_INFO_S("Setting up the VL6180 ToF Sensor...\n");
    struct i2c_device *vl6180 = vl6180_setup();
    if (vl6180 == NULL)
        LOG_ERROR_S("Failed to set up vl6180\n");
    while (1)
    {
        printf("range: %dmm\n", vl6180->read(vl6180));
    }

    return 0;
}
