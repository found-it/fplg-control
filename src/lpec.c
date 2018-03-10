/*
 *  File:   lpec.c
 *  Author: James Petersen <jpetersenames@gmail.com>
 */

#include "../include/lpec.h"
#include "../include/base.h"
#include "../include/logging.h"
#include "../include/vl6180.h"
#include "../include/tmp007.h"

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

    LOG_INFO_S("Setting up the TMP007 Temperature Sensor...\n");
    int tfd = tmp007_setup();
    int i = 0;
    while (i < 10)
    {
        printf("temp:  %0.2f F\n", tmp007_read_temp(tfd));
        printf("range: %d mm\n", vl6180->read(vl6180));
        ++i;
    }

    return 0;
}
