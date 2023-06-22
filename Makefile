CC=g++
INCLUDE_DIR := $(shell pwd)/include
BIN_DIR := $(shell pwd)/bin/linux
OBJ_DIR := $(shell pwd)/obj
SRC := $(shell pwd)/src
CFLAGS := -std=c++20 -m64 -g -Wall
LFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx
OBJECTS = objdir compilesrc

all: $(OBJECTS)
	$(CC) $(OBJ_DIR)/*.o -o $(BIN_DIR)/main $(LFLAGS)
	rm -r $(OBJ_DIR)

objdir:
	mkdir -p $(OBJ_DIR)

compilesrc:
	$(CC) -c $(SRC)/*.cpp $(CFLAGS) -I$(INCLUDE_DIR) 
	mv $(shell pwd)/*.o $(OBJ_DIR)

clean:
	rm -r $(shell pwd)/obj
