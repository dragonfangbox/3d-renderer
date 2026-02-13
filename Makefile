CC := gcc
CFLAGS := -Wall -std=c11
DFLAGS := -fsanitize=address -g -O0
INCLUDES := -Iinclude
LIBS := `pkg-config --cflags --libs sdl2 SDL2_image` -lGL -ldl
CFILES := $(wildcard src/*.c)

.PHONY: build debug

build:
	$(CC) $(CFLAGS) $(INCLUDES) $(CFILES) -o main $(LIBS)

debug:
	$(CC) $(CLFAGS) $(DFLAGS) $(INCLUDES) $(CFILES) -o main $(LIBS)



