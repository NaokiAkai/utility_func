SHELL = /bin/bash

TARGET = libutility_funcs
PACKAGE = $(TARGET)

INC = utility_funcs.hpp
SRC = utility_funcs.cpp
OBJ = $(SRC:.cpp=.o)

DEFS   =
CFLAGS = -Wall -O2 -c -lm -I$(HOME)/include -I. -L$(HOME)/lib

CC = g++

.cpp.o:
	$(CC) $(CFLAGS) $<

all: $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET).a *~

$(TARGET): $(OBJ)
	$(AR) -r $@.a $(OBJ)
	ranlib $@.a

install: $(TARGET)
	@if ! test -d $(HOME)/lib; then  mkdir $(HOME)/lib; fi
	@if ! test -d $(HOME)/include; then  mkdir $(HOME)/include; fi
	cp -p $(TARGET).a $(HOME)/lib
	cp -p $(INC) $(HOME)/include

uninstall: 
	rm -f $(HOME)/lib/$(TARGET).a
	rm -f $(HOME)/include/$(INC)

