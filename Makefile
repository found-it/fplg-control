######################################################
#
#   File:   Makefile
#   Author: James Petersen <jpetersenames@gmail.com>
#
######################################################

CC      = gcc
CFLAGS  = -Wall

OBJ     = logging.o lpec.o vl6180.o

TARGET  = fplg

fplg: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

lpec.o: src/lpec.c include/*.h
	$(CC) $(CFLAGS) -c src/lpec.c

logging.o: src/logging.c include/logging.h
	$(CC) $(CFLAGS) -c src/logging.c

vl6180.o: src/vl6180.c include/vl6180.h
	$(CC) $(CFLAGS) -c src/vl6180.c

clean:
	rm -f $(OBJ) $(TARGET)
