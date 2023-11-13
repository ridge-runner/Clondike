CC=gcc
CFLAGS=-Wall -std=c18 -g
LIBS=-lraylib

# Define your source and obj files
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

# Main target

Clondike: $(OBJ)
	$(CC) $(CFLAGS) -o bin/$@ $^ $(LIBS)

# Generic rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up
clean:
	rm -f $(OBJ) bin/clondike

# phony targets
.PHONY: clean
