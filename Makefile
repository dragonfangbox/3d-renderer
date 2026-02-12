CC := gcc
CFLAGS := -Wall -std=c11
INCLUDES := -Iinclude
LIBS := `pkg-config --cflags --libs sdl2 SDL2_image` -lGL -ldl
CFILES := $(wildcard src/*.c)

.PHONY: build

build:
	$(CC) $(CFLAGS) $(INCLUDES) $(CFILES) -o main $(LIBS)
