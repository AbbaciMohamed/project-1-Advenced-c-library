# Compiler
CC = gcc

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TEST_DIR = test

# Output file
TARGET = $(BUILD_DIR)/part1_project

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(TEST_DIR)/main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Flags
CFLAGS = -I$(INC_DIR) -Wall -Wextra -g

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Build complete. Run with: ./$(TARGET)"

# Clean build files
clean:
	rm -rf $(BUILD_DIR) *.o $(SRC_DIR)/*.o $(TEST_DIR)/*.o
	@echo "Cleaned build artifacts."

# Run the program
run: all
	./$(TARGET)

