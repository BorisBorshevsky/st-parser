# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Volumes/CLion/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Volumes/CLion/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/boris/CLionProjects/gil

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/boris/CLionProjects/gil/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/gil.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gil.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gil.dir/flags.make

CMakeFiles/gil.dir/main.c.o: CMakeFiles/gil.dir/flags.make
CMakeFiles/gil.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/boris/CLionProjects/gil/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gil.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gil.dir/main.c.o   -c /Users/boris/CLionProjects/gil/main.c

CMakeFiles/gil.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gil.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/boris/CLionProjects/gil/main.c > CMakeFiles/gil.dir/main.c.i

CMakeFiles/gil.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gil.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/boris/CLionProjects/gil/main.c -o CMakeFiles/gil.dir/main.c.s

CMakeFiles/gil.dir/main.c.o.requires:

.PHONY : CMakeFiles/gil.dir/main.c.o.requires

CMakeFiles/gil.dir/main.c.o.provides: CMakeFiles/gil.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/gil.dir/build.make CMakeFiles/gil.dir/main.c.o.provides.build
.PHONY : CMakeFiles/gil.dir/main.c.o.provides

CMakeFiles/gil.dir/main.c.o.provides.build: CMakeFiles/gil.dir/main.c.o


# Object files for target gil
gil_OBJECTS = \
"CMakeFiles/gil.dir/main.c.o"

# External object files for target gil
gil_EXTERNAL_OBJECTS =

gil: CMakeFiles/gil.dir/main.c.o
gil: CMakeFiles/gil.dir/build.make
gil: CMakeFiles/gil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/boris/CLionProjects/gil/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable gil"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gil.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gil.dir/build: gil

.PHONY : CMakeFiles/gil.dir/build

CMakeFiles/gil.dir/requires: CMakeFiles/gil.dir/main.c.o.requires

.PHONY : CMakeFiles/gil.dir/requires

CMakeFiles/gil.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gil.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gil.dir/clean

CMakeFiles/gil.dir/depend:
	cd /Users/boris/CLionProjects/gil/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/boris/CLionProjects/gil /Users/boris/CLionProjects/gil /Users/boris/CLionProjects/gil/cmake-build-debug /Users/boris/CLionProjects/gil/cmake-build-debug /Users/boris/CLionProjects/gil/cmake-build-debug/CMakeFiles/gil.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gil.dir/depend
