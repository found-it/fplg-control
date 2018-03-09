/*
 *  File:   vl6180.c
 *  Author: James Petersen <jpetersenames@gmail.com>
 */

#include "../include/vl6180.h"


/* 
 *  register union, used for quick access to bytes. 
 */
typedef union vl6180_register
{
    uint16_t name;
    uint8_t  byte[2];
} vregister_t;


/*
 *  static function prototypes
 */
static ssize_t write_data8(int fd, uint16_t regi, uint8_t data);
static uint8_t read_data8(int fd, uint16_t regi);
static int configure_settings(int fd);


/*  setup()
 *  RETURNS: file descriptor if setup is good, ERROR on error */
i2c_dev_t *vl6180_setup()
{
    i2c_dev_t *tmp = malloc(sizeof(i2c_dev_t));
    int stat = 0;

    tmp->addr = VL6180_ID;
    tmp->dev  = VL6180_DEV;
    tmp->read = vl6180_read_range;

    /*
     *   open up the device
     */
    if ((tmp->fd = open(tmp->dev, O_RDWR)) < 0)
    {
        LOG_ERROR_S("Opening VL6180\n");
        return NULL;
    }
    else
        LOG_INFO_S("VL6180 Opened Successfully\n");

    /*
     *   initialize the device as a slave
     */
    if (ioctl(tmp->fd, I2C_SLAVE, tmp->addr) < 0)
    {
        LOG_ERROR_S("Initializing Communication with VL6180\n");
        return NULL;
    }
    else
        LOG_INFO_S("VL6180 Communication Initialized\n");

    /*
     *   check if fresh out of reset
     */
    while (((stat = read_data8(tmp->fd, 0x016)) & 0x01) != 0x01);
    LOG_INFO("Fresh out of reset: %0x\n", stat);

    /*
     *   Configure with settings from datasheet
     */
    if ((stat = configure_settings(tmp->fd)) != SUCCESS)
        LOG_ERROR("Configuring VL6180 on line %d\n", stat);

    /*
     *   Write 0x00 to fresh out of reset register
     */
    if (write_data8(tmp->fd, 0x016, 0x00) < 0) 
        LOG_ERROR_S("Fresh out of reset register not written to.\n");

    return tmp;
}/* vl6180_setup */


/*  configure_settings()
 *  RETURNS: SUCCESS if good, ERROR on error */
static int configure_settings(int fd)
{
    /*
    **  Mandatory : private registers 
    */
    if (write_data8(fd, 0x0207, 0x01) < 0) return __LINE__;
    if (write_data8(fd, 0x0208, 0x01) < 0) return __LINE__;
    if (write_data8(fd, 0x0096, 0x00) < 0) return __LINE__;
    if (write_data8(fd, 0x0097, 0xfd) < 0) return __LINE__;
    if (write_data8(fd, 0x00e3, 0x00) < 0) return __LINE__;
    if (write_data8(fd, 0x00e4, 0x04) < 0) return __LINE__;
    if (write_data8(fd, 0x00e5, 0x02) < 0) return __LINE__;
    if (write_data8(fd, 0x00e6, 0x01) < 0) return __LINE__;
    if (write_data8(fd, 0x00e7, 0x03) < 0) return __LINE__;
    if (write_data8(fd, 0x00f5, 0x02) < 0) return __LINE__;
    if (write_data8(fd, 0x00d9, 0x05) < 0) return __LINE__;
    if (write_data8(fd, 0x00db, 0xce) < 0) return __LINE__;
    if (write_data8(fd, 0x00dc, 0x03) < 0) return __LINE__;
    if (write_data8(fd, 0x00dd, 0xf8) < 0) return __LINE__;
    if (write_data8(fd, 0x009f, 0x00) < 0) return __LINE__;
    if (write_data8(fd, 0x00a3, 0x3c) < 0) return __LINE__;
    if (write_data8(fd, 0x00b7, 0x00) < 0) return __LINE__;
    if (write_data8(fd, 0x00bb, 0x3c) < 0) return __LINE__;
    if (write_data8(fd, 0x00b2, 0x09) < 0) return __LINE__;
    if (write_data8(fd, 0x00ca, 0x09) < 0) return __LINE__;
    if (write_data8(fd, 0x0198, 0x01) < 0) return __LINE__;
    if (write_data8(fd, 0x01b0, 0x17) < 0) return __LINE__;
    if (write_data8(fd, 0x01ad, 0x00) < 0) return __LINE__;
    if (write_data8(fd, 0x00ff, 0x05) < 0) return __LINE__;
    if (write_data8(fd, 0x0100, 0x05) < 0) return __LINE__;
    if (write_data8(fd, 0x0199, 0x05) < 0) return __LINE__;
    if (write_data8(fd, 0x01a6, 0x1b) < 0) return __LINE__;
    if (write_data8(fd, 0x01ac, 0x3e) < 0) return __LINE__;
    if (write_data8(fd, 0x01a7, 0x1f) < 0) return __LINE__;
    if (write_data8(fd, 0x0030, 0x00) < 0) return __LINE__;

    /*
    **  Recommended : Public registers - See data sheet for more detail
    */
    /* Enables polling for ‘New Sample ready’ when measurement completes */
    if (write_data8(fd, 0x0011, 0x10) < 0) return __LINE__;

    /* Set the averaging sample period (compromise between lower noise
       and increased execution time) */
    if (write_data8(fd, 0x010a, 0x30) < 0) return __LINE__;

    /* Sets the light and dark gain (upper nibble). Dark gain should 
       not be changed. */
    if (write_data8(fd, 0x003f, 0x46) < 0) return __LINE__;

    /* sets the # of range measurements after which auto calibration 
       of system is performed */
    if (write_data8(fd, 0x0031, 0xFF) < 0) return __LINE__;

    /* Set ALS integration time to 100ms */
    if (write_data8(fd, 0x0040, 0x63) < 0) return __LINE__;

    /* perform a single temperature calibration of the ranging sensor */
    if (write_data8(fd, 0x002e, 0x01) < 0) return __LINE__;

    /*
    ** Optional: Public registers - See data sheet for more detail 
    */
    /* Set default ranging inter-measurement period to 100ms */
    if (write_data8(fd, 0x001b, 0x09) < 0) return __LINE__;

    /* Set default ALS inter-measurement period to 500ms */
    if (write_data8(fd, 0x003e, 0x31) < 0) return __LINE__;

    /* Configures interrupt on ‘New Sample Ready threshold event’ */
    if (write_data8(fd, 0x0014, 0x24) < 0) return __LINE__;
    return SUCCESS;
}/* configure_settings */


/*  read_data8()
 *  RETURNS: 1 byte of data, ERROR otherwise */
static uint8_t read_data8(int fd, uint16_t regi)
{
    uint8_t reg_addr[2];
    uint8_t data;
    ssize_t len;
    vregister_t r;

    /* flip the Intel little-endianess */
    r.name = regi;
    reg_addr[0] = r.byte[1];
    reg_addr[1] = r.byte[0];

    if ((len = write(fd, reg_addr, sizeof(reg_addr))) < 0)
    {
        LOG_ERROR("Register not written, value returned: %d\n", len);
        return ERROR;
    }

    if ((len = read(fd, &data, sizeof(data))) < 0)
    {
        LOG_ERROR("Register not read, value returned: %d\n", len);
        return ERROR;
    }

    return data;
}/* read_data8 */

/*  write_data8()
 *  RETURNS: number of bytes written, -1 on error.  */
static ssize_t write_data8(int fd, uint16_t regi, uint8_t data)
{
    uint8_t buf[3];
    vregister_t r;

    /*
     *  flip the Intel little-endianess
     */
    r.name = regi;
    buf[0] = r.byte[1];
    buf[1] = r.byte[0];
    buf[2] = data;

    return write(fd, buf, sizeof(buf));
}/* write_data8 */


/*  vl6180_read_range()
 *  RETURNS: 1 byte range value in mm, ERROR otherwise
 *  TODO: add error checks */
uint8_t vl6180_read_range(i2c_dev_t *self)
{

    int fd = self->fd;
    uint8_t stat;
    stat = read_data8(fd, 0x04d);

    stat = write_data8(fd, 0x018, 0x01);

    while (((stat = read_data8(fd, 0x04f)) & 0x07) != 0x04);
    uint8_t range = read_data8(fd, 0x063);

    stat = write_data8(fd, 0x015, 0x07);
    return range;
}/* vl6180_read_range */
