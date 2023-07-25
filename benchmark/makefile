# Directories
INCLUDE_DIR := ./include
SOURCE_DIR := ./src
BUILD_DIR := ./build
DEBUG_DIR := ./debug
PROFILE_DIR := ./profile

# Compiler and flags
CC := g++ -std=c++17
CFLAGS := -Wall -Wextra -I$(INCLUDE_DIR)

# Debug flags
DEBUG_FLAGS := -g

# Profile flags
PROFILE_FLAGS := -O0 -pg

# List of source files
SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)

# Generate object file names for build and debug directories
BUILD_OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
DEBUG_OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp, $(DEBUG_DIR)/%.o, $(SOURCES))

# Default target: build and debug
all: build debug

# Rule to build the program in the build directory
build: $(BUILD_DIR)

$(BUILD_DIR): $(BUILD_OBJECTS)
	$(CC) $(CFLAGS) $(BUILD_OBJECTS) -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the program with debug information in the debug directory
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(DEBUG_DIR)

$(DEBUG_DIR): $(DEBUG_OBJECTS)
	$(CC) $(CFLAGS) $(DEBUG_OBJECTS) -o $@

$(DEBUG_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to profile the program
profile: CFLAGS += $(PROFILE_FLAGS)
profile: $(INCLUDE_DIR)
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) $(SOURCE_DIR)/eager.cpp -o $(BUILD_DIR)/eager.o
	$(BUILD_DIR)/eager.o
	gprof $(BUILD_DIR)/eager.o $(BUILD_DIR)/gmon.out |
 	gprof2dot -s -w gprof $(PROFILE_DIR)/profile.txt | 
	dot -Gdpi=200 -Tpng -o $(PROFILE_DIR)/profile.png



# Clean
clean:
	rm -rf $(BUILD_DIR) $(DEBUG_DIR) $(PROFILE_DIR) *.png gmon.out profile.txt
