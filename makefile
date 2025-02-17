# Makefile for compiling myshell on macOS
# Uses Clang as the default compiler, but GCC can also be used.

CC = clang                  # Compiler (Clang is the default on macOS)
CFLAGS = -Wall -Wextra -std=c99  # Compiler flags: show warnings, use C99 standard
TARGET = myshell            # Name of the output executable
OBJS = myshell.o utility.o  # List of object files needed to build the executable

# Default rule: build the myshell executable
all: $(TARGET)

# Linking step: Generate myshell binary from object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile myshell.c into an object file
myshell.o: myshell.c myshell.h
	$(CC) $(CFLAGS) -c myshell.c

# Compile utility.c into an object file
utility.o: utility.c myshell.h
	$(CC) $(CFLAGS) -c utility.c

# Clean rule: Remove compiled files
clean:
	rm -f $(TARGET) $(OBJS)
