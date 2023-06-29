CC = g++
INCLUDE_DIR := include
BIN_DIR := bin/linux
SRC_DIR := src
OBJ_DIR := obj

SOURCES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

CFLAGS := -std=c++20 -m64 -g -Wall
LFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx

.PHONY: all clean

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(OBJECTS)
	$(CC) $^ -o $@ $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS) -I$(INCLUDE_DIR)

clean:
	rm -rf $(BIN_DIR)/*
	rm -rf $(OBJ_DIR)/*
