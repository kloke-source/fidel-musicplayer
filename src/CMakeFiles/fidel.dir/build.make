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
include src/CMakeFiles/fidel.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/fidel.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/fidel.dir/flags.make

src/CMakeFiles/fidel.dir/main.cpp.o: src/CMakeFiles/fidel.dir/flags.make
src/CMakeFiles/fidel.dir/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/fidel.dir/main.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src && /usr/lib/hardening-wrapper/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fidel.dir/main.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/main.cpp

src/CMakeFiles/fidel.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fidel.dir/main.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src && /usr/lib/hardening-wrapper/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/main.cpp > CMakeFiles/fidel.dir/main.cpp.i

src/CMakeFiles/fidel.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fidel.dir/main.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src && /usr/lib/hardening-wrapper/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/main.cpp -o CMakeFiles/fidel.dir/main.cpp.s

src/CMakeFiles/fidel.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/fidel.dir/main.cpp.o.requires

src/CMakeFiles/fidel.dir/main.cpp.o.provides: src/CMakeFiles/fidel.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/fidel.dir/build.make src/CMakeFiles/fidel.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/fidel.dir/main.cpp.o.provides

src/CMakeFiles/fidel.dir/main.cpp.o.provides.build: src/CMakeFiles/fidel.dir/main.cpp.o


# Object files for target fidel
fidel_OBJECTS = \
"CMakeFiles/fidel.dir/main.cpp.o"

# External object files for target fidel
fidel_EXTERNAL_OBJECTS =

fidel_debug: src/CMakeFiles/fidel.dir/main.cpp.o
fidel_debug: src/CMakeFiles/fidel.dir/build.make
fidel_debug: src/GUI/libGUI_debug.a
fidel_debug: src/Audio/libAudio_debug.a
fidel_debug: src/Spectrum/libSpectrum_debug.a
fidel_debug: src/Utilities/libUtilities_debug.a
fidel_debug: src/CMakeFiles/fidel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../fidel_debug"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fidel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/fidel.dir/build: fidel_debug

.PHONY : src/CMakeFiles/fidel.dir/build

src/CMakeFiles/fidel.dir/requires: src/CMakeFiles/fidel.dir/main.cpp.o.requires

.PHONY : src/CMakeFiles/fidel.dir/requires

src/CMakeFiles/fidel.dir/clean:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src && $(CMAKE_COMMAND) -P CMakeFiles/fidel.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/fidel.dir/clean

src/CMakeFiles/fidel.dir/depend:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src /home/tashrif/Dev/fidel-musicplayer-cmake/src/CMakeFiles/fidel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/fidel.dir/depend

