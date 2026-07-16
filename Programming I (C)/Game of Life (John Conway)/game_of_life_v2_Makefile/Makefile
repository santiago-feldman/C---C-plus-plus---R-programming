# Using minGW and VScode on Windows 10, write >>mingw32-make to create the .o and .exe files.
# Use >>mingw32-make clean to delete intermediate object files (.o).
# Use >>mingw32-make run to run the program on the current terminal.

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g  # Enable all warnings and debugging info

# Detect terminal and set clean command
ifeq ($(OS),Windows_NT)
  RM = del /f
else
  RM = rm -f
endif

# Source files
SRC = $(wildcard *.c)  # Automatically gets all .c files in the current directory
OBJ = $(SRC:.c=.o)     # Converts .c files to .o files

# Name of the output executable
EXEC = gameoflifev2

# Default target to build the program
all: $(EXEC)

# Rule to link the object files into an executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up intermediate files and executable
clean:
	$(RM) $(OBJ) $(EXEC)

# Target to run the program after building
run: $(EXEC)
	./$(EXEC)

# Phony targets (not actual files)
.PHONY: all clean run
