# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat/build

# Include any dependencies generated for this target.
include CMakeFiles/LazyMat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LazyMat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LazyMat.dir/flags.make

CMakeFiles/LazyMat.dir/src/main.cpp.o: CMakeFiles/LazyMat.dir/flags.make
CMakeFiles/LazyMat.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LazyMat.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LazyMat.dir/src/main.cpp.o -c /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat/src/main.cpp

CMakeFiles/LazyMat.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LazyMat.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat/src/main.cpp > CMakeFiles/LazyMat.dir/src/main.cpp.i

CMakeFiles/LazyMat.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LazyMat.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat/src/main.cpp -o CMakeFiles/LazyMat.dir/src/main.cpp.s

# Object files for target LazyMat
LazyMat_OBJECTS = \
"CMakeFiles/LazyMat.dir/src/main.cpp.o"

# External object files for target LazyMat
LazyMat_EXTERNAL_OBJECTS =

bin/LazyMat: CMakeFiles/LazyMat.dir/src/main.cpp.o
bin/LazyMat: CMakeFiles/LazyMat.dir/build.make
bin/LazyMat: CMakeFiles/LazyMat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/LazyMat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LazyMat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LazyMat.dir/build: bin/LazyMat

.PHONY : CMakeFiles/LazyMat.dir/build

CMakeFiles/LazyMat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LazyMat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LazyMat.dir/clean

CMakeFiles/LazyMat.dir/depend:
	cd /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat/build /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat/build /mnt/c/Users/ddamiana/Documents/CodeProjects/personal/LazyMat/build/CMakeFiles/LazyMat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LazyMat.dir/depend

