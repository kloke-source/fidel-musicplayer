# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/tashrif/Dev/fidel-musicplayer-cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tashrif/Dev/fidel-musicplayer-cmake

# Include any dependencies generated for this target.
include src/Utilities/CMakeFiles/Utilities.dir/depend.make

# Include the progress variables for this target.
include src/Utilities/CMakeFiles/Utilities.dir/progress.make

# Include the compile flags for this target's objects.
include src/Utilities/CMakeFiles/Utilities.dir/flags.make

src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o: src/Utilities/CMakeFiles/Utilities.dir/flags.make
src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o: src/Utilities/util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utilities.dir/util.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities/util.cpp

src/Utilities/CMakeFiles/Utilities.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utilities.dir/util.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities/util.cpp > CMakeFiles/Utilities.dir/util.cpp.i

src/Utilities/CMakeFiles/Utilities.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utilities.dir/util.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities/util.cpp -o CMakeFiles/Utilities.dir/util.cpp.s

src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.requires:

.PHONY : src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.requires

src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.provides: src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.requires
	$(MAKE) -f src/Utilities/CMakeFiles/Utilities.dir/build.make src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.provides.build
.PHONY : src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.provides

src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.provides.build: src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o


# Object files for target Utilities
Utilities_OBJECTS = \
"CMakeFiles/Utilities.dir/util.cpp.o"

# External object files for target Utilities
Utilities_EXTERNAL_OBJECTS =

src/Utilities/libUtilities.a: src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o
src/Utilities/libUtilities.a: src/Utilities/CMakeFiles/Utilities.dir/build.make
src/Utilities/libUtilities.a: src/Utilities/CMakeFiles/Utilities.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libUtilities.a"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities && $(CMAKE_COMMAND) -P CMakeFiles/Utilities.dir/cmake_clean_target.cmake
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Utilities.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Utilities/CMakeFiles/Utilities.dir/build: src/Utilities/libUtilities.a

.PHONY : src/Utilities/CMakeFiles/Utilities.dir/build

src/Utilities/CMakeFiles/Utilities.dir/requires: src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.requires

.PHONY : src/Utilities/CMakeFiles/Utilities.dir/requires

src/Utilities/CMakeFiles/Utilities.dir/clean:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities && $(CMAKE_COMMAND) -P CMakeFiles/Utilities.dir/cmake_clean.cmake
.PHONY : src/Utilities/CMakeFiles/Utilities.dir/clean

src/Utilities/CMakeFiles/Utilities.dir/depend:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities /home/tashrif/Dev/fidel-musicplayer-cmake/src/Utilities/CMakeFiles/Utilities.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Utilities/CMakeFiles/Utilities.dir/depend
