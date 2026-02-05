CC := gcc
CFLAGS := -Wall -Wextra
CFILES := main.c

INCLUDES := -I./include

.PHONY: build

build:
	$(CC) $(CFLAGS) -o main $(CFILES) $(INCLUDES)

