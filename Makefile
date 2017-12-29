######################################################
#
#   File:   Makefile
#   Author: James Petersen <jpetersenames@gmail.com>
#
######################################################

CC      = gcc
CFLAGS  = -Wall

OBJ     = logging.o lpec.o

TARGET  = out

out: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

lpec.o: src/lpec.c include/*.h
	$(CC) $(CFLAGS) -c src/lpec.c

logging.o: src/logging.c include/logging.h
	$(CC) $(CFLAGS) -c src/logging.c

clean:
	rm -f $(OBJ) $(TARGET)
