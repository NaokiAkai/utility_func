SHELL = /bin/bash

TARGET = libutility_funcs
PACKAGE = $(TARGET)

INC = utility_funcs.hpp
SRC = utility_funcs.cpp
OBJ = $(SRC:.cpp=.o)

DEFS   =
CFLAGS = -Wall -O2 -c -lm -I/usr/include -I/usr/local/include -I. -L/usr/lib -L/usr/local/lib

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
	cp -p $(TARGET).a /usr/local/lib
	cp -p $(INC) /usr/local/include

uninstall: 
	rm -f /usr/local/lib/$(TARGET).a
	rm -f /usr/local/include/$(INC)

