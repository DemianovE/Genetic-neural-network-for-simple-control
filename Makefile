# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -I TOOLBOX/GENETIC/include

# Source files and object files
MAIN_SRC = ./main.c
MAIN_OBJ = $(MAIN_SRC:.c=.o)

# Find all .c and .h files in subdirectories
C_FILES := $(shell find . -type f -name '*.c' -not -path './.*')
H_FILES := $(shell find . -type f -name '*.h' -not -path './.*')

# Executable name
EXECUTABLE = myprogram

all: $(EXECUTABLE)

$(EXECUTABLE): $(MAIN_OBJ) $(C_FILES:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^

$(MAIN_OBJ): $(MAIN_SRC) $(H_FILES)
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE) $(MAIN_OBJ) $(C_FILES:.c=.o)
