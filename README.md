# fplg-control
## Ohio University - Free Piston Linear Generator Control Code
### James Petersen

This is the control code for the Free Piston Linear Generator.

This source code includes modules for an I2C interface for the VL6180 ToF distance sensor, as well as an I2C interface for the TMP007 Temperature Sensor.

This module is built and run on a Raspberry Pi 3 running Raspbian Stretch <version>

### Installation
Simply clone this repository and then type `make` and the project will be built into the `fplg` executable.

### Dependencies
The following dependencies must be installed before the project can be documented:
```shell

sudo apt-get install doxygen


```

### Doxygen Documentation
Included in this project is Doxygen support. Simply type `make doc` and Doxygen will be run to create the documentation. All of the documentation is put into the hidden filed `.docfiles` and then the relevent documentation is symbolicly linked in the `doc/` folder. This is to reduce the clutter of Doxygen output and make it obvious which documents to look at.
