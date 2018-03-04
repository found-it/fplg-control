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

static int write_data8(int fd, uint16_t regi, uint8_t data);
static int read_data8(int fd, uint16_t regi);
static int configure_settings(int fd);

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
        LOG_INFO_S("VL6180 Opened Successfully\n");
    
    /*
     *   initialize the device as a slave
     */
    if (ioctl(fd, I2C_SLAVE, id) < 0)
    {
        LOG_ERROR_S("Initializing Communication with VL6180\n");
        return ERROR;
    }
    else
        LOG_INFO_S("VL6180 Communication Initialized\n");

    /*
     *   check if fresh out of reset
     */
    ready = read_data8(fd, 0x016);
    LOG_DEBUG("Fresh out of reset: %0x\n", ready);

    /* TODO: Check for errors */
    configure_settings(fd);

    return fd;
}

static int configure_settings(int fd)
{
    /*
     *   load with settings from datasheet
     */
    // Mandatory : private registers
    if (write_data8(fd, 0x0207, 0x01) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x0208, 0x01) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x0096, 0x00) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x0097, 0xfd) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00e3, 0x00) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00e4, 0x04) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00e5, 0x02) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00e6, 0x01) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00e7, 0x03) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00f5, 0x02) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00d9, 0x05) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00db, 0xce) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00dc, 0x03) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00dd, 0xf8) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x009f, 0x00) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00a3, 0x3c) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00b7, 0x00) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00bb, 0x3c) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00b2, 0x09) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00ca, 0x09) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x0198, 0x01) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x01b0, 0x17) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x01ad, 0x00) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x00ff, 0x05) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x0100, 0x05) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x0199, 0x05) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x01a6, 0x1b) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x01ac, 0x3e) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x01a7, 0x1f) < 0) printf("0x0207\n");
    if (write_data8(fd, 0x0030, 0x00) < 0) printf("0x0207\n");

    // Recommended : Public registers - See data sheet for more detail

    // Enables polling for ‘New Sample ready’ when measurement completes
    if (write_data8(fd, 0x0011, 0x10) < 0) printf("0x0207\n"); 
    
    // Set the averaging sample period (compromise between lower noise and increased execution time)
    if (write_data8(fd, 0x010a, 0x30) < 0) printf("0x0207\n"); 
    
    // Sets the light and dark gain (upper nibble). Dark gain should not be changed.
    if (write_data8(fd, 0x003f, 0x46) < 0) printf("0x0207\n"); 
    
    // sets the # of range measurements after which auto calibration of system is performed
    if (write_data8(fd, 0x0031, 0xFF) < 0) printf("0x0207\n"); 

    // Set ALS integration time to 100ms
    if (write_data8(fd, 0x0040, 0x63) < 0) printf("0x0207\n"); 

    // perform a single temperature calibration of the ranging sensor
    if (write_data8(fd, 0x002e, 0x01) < 0) printf("0x0207\n"); 

    //Optional: Public registers - See data sheet for more detail
    
    // Set default ranging inter-measurement period to 100ms
    if (write_data8(fd, 0x001b, 0x09) < 0) printf("0x0207\n"); 
    
    // Set default ALS inter-measurement period to 500ms
    if (write_data8(fd, 0x003e, 0x31) < 0) printf("0x0207\n"); 

    // Configures interrupt on ‘New Sample Ready threshold event’
    if (write_data8(fd, 0x0014, 0x24) < 0) printf("0x0207\n"); 

    return SUCCESS;
}

static int read_data8(int fd, uint16_t regi)
{
    uint8_t reg_addr[2];
    uint8_t data;
    int     len;
    reg_t   r;
    r.name = regi;

    /*
     *  flip the Intel little-endianess
     */
    reg_addr[0] = r.byte[1];
    reg_addr[1] = r.byte[0];
    
    if ((len = write(fd, reg_addr, sizeof(reg_addr))) < 0)
    {
        LOG_ERROR("Register not written, value returned: %d\n", len);
        return ERROR;
    }

    if ((len = read(fd, &data, sizeof(data))) < 0)
    {
        LOG_ERROR("Register not written, value returned: %d\n", len);
        return ERROR;
    }

    return data;
}


static int write_data8(int fd, uint16_t regi, uint8_t data)
{
    uint8_t buf[3];
    reg_t   r;
    r.name = regi;
    buf[0] = r.byte[1];
    buf[1] = r.byte[0];
    buf[2] = data;

    return write(fd, buf, sizeof(buf));
}

int vl6180_read_range(int fd)
{
    return SUCCESS;
}
