/*****************************************************
 *
 *  File:   lpec.c
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 *****************************************************
 */

#include "../include/lpec.h"
#include <stdio.h>

int main()
{
    printf("\n\n");

    LOG_ERROR("this is an error: %d\n", 123);
    printf("\n");
    LOG_DEBUG("this is an debug: %d\n", 123);
    printf("\n");
    LOG_WARN("this is an warn: %d\n", 123);
    printf("\n");
    LOG_INFO("this is an info: %d\n", 123);

    printf("\n\n\n");

#if 0
    int vl_fd = setup(DEVICE, DEFAULT_ID);
    int range = 0;
    for (int i = 0; i < 63; ++i)
        range += vl6180_read_range(vl_fd);
    printf("range: %dmm\n", range>>6);
#endif

    i2c_dev_t *vl6180 = vl6180_setup();
    if (vl6180 == NULL)
        LOG_ERROR_S("Failed to set up vl6180\n");
    printf("range: %dmm\n", vl6180->read(vl6180));

    return 0;
}
