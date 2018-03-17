##
#   File:   Makefile
#   Author: James Petersen <jpetersenames@gmail.com>
#
#   Usage:
#       make
#       make doc
#       make clean
##

CC      = gcc
CFLAGS  = -Wall

OBJ     = logging.o lpec.o vl6180.o tmp007.o

TARGET  = fplg

fplg: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

lpec.o: src/lpec.c include/*.h
	$(CC) $(CFLAGS) -c src/lpec.c

logging.o: src/logging.c include/logging.h
	$(CC) $(CFLAGS) -c src/logging.c

vl6180.o: src/vl6180.c include/vl6180.h
	$(CC) $(CFLAGS) -c src/vl6180.c

tmp007.o: src/tmp007.c include/tmp007.h
	$(CC) $(CFLAGS) -c src/tmp007.c

doc: src/* include/* Doxyfile
	doxygen Doxyfile
	mkdir -p doc
	cd doc && ln -sf ../.docfiles/html/index.html lpec_documentation.html


clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf .docfiles doc
