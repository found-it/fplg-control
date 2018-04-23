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
ifeq (, $(shell which doxygen))
	@echo "\033[31mDoxygen is not installed.\033[0m"
	@echo "\033[32mInstalling using \033[36msudo apt-get install doxygen\033[0m"
	sudo apt-get install doxygen
endif
ifeq (, $(shell which graphviz))
	@echo "\033[31mDoxygen needs the dot utility."
	@echo "\033[32mInstalling graphviz-dot using \033[36msudo apt-get install graphviz\033[0m"
	sudo apt-get install graphviz
endif
	doxygen Doxyfile
	mkdir -p doc
	@echo "\033[92mSymbolically linking the documentation HTML file into doc/\033[0m"
	cd doc && ln -sf ../.docfiles/html/index.html lpec_documentation.html

clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf .docfiles doc
