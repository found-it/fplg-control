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
    $(error Doxygen is not installed.)
endif
	doxygen Doxyfile
	mkdir -p doc
	@echo "\033[92mSymbolically linking the documentation HTML file into doc/\033[0m"
	cd doc && ln -sf ../.docfiles/html/index.html lpec_documentation.html
ifeq (, $(shell which pdflatex))
    $(error pdflatex is not installed. See dependencies in README.md)
endif
	cd .docfiles/latex && make
	cp .docfiles/latex/refman.pdf doc/lpec_documentation.pdf
	@echo "\033[92mCreated PDF documentation in doc/\033[0m"

clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf .docfiles doc
