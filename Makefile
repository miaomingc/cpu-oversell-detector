# Makefile for cpu-oversell-detector

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2

# Linker flags
LDFLAGS = -lm -lpthread

# Target executable
TARGET = cpu-oversell-detector

# Source files
SRCS = main.c cpu_load.c cpu_monitor.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean