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
CMAKE_BINARY_DIR = /home/tashrif/Dev/fidel-musicplayer-cmake/build

# Include any dependencies generated for this target.
include src/Audio/CMakeFiles/Audio.dir/depend.make

# Include the progress variables for this target.
include src/Audio/CMakeFiles/Audio.dir/progress.make

# Include the compile flags for this target's objects.
include src/Audio/CMakeFiles/Audio.dir/flags.make

src/Audio/CMakeFiles/Audio.dir/playback.cpp.o: src/Audio/CMakeFiles/Audio.dir/flags.make
src/Audio/CMakeFiles/Audio.dir/playback.cpp.o: ../src/Audio/playback.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Audio/CMakeFiles/Audio.dir/playback.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/Audio && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Audio.dir/playback.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio/playback.cpp

src/Audio/CMakeFiles/Audio.dir/playback.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Audio.dir/playback.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/Audio && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio/playback.cpp > CMakeFiles/Audio.dir/playback.cpp.i

src/Audio/CMakeFiles/Audio.dir/playback.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Audio.dir/playback.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/Audio && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio/playback.cpp -o CMakeFiles/Audio.dir/playback.cpp.s

src/Audio/CMakeFiles/Audio.dir/playback.cpp.o.requires:

.PHONY : src/Audio/CMakeFiles/Audio.dir/playback.cpp.o.requires

src/Audio/CMakeFiles/Audio.dir/playback.cpp.o.provides: src/Audio/CMakeFiles/Audio.dir/playback.cpp.o.requires
	$(MAKE) -f src/Audio/CMakeFiles/Audio.dir/build.make src/Audio/CMakeFiles/Audio.dir/playback.cpp.o.provides.build
.PHONY : src/Audio/CMakeFiles/Audio.dir/playback.cpp.o.provides

src/Audio/CMakeFiles/Audio.dir/playback.cpp.o.provides.build: src/Audio/CMakeFiles/Audio.dir/playback.cpp.o


# Object files for target Audio
Audio_OBJECTS = \
"CMakeFiles/Audio.dir/playback.cpp.o"

# External object files for target Audio
Audio_EXTERNAL_OBJECTS =

src/Audio/libAudio.a: src/Audio/CMakeFiles/Audio.dir/playback.cpp.o
src/Audio/libAudio.a: src/Audio/CMakeFiles/Audio.dir/build.make
src/Audio/libAudio.a: src/Audio/CMakeFiles/Audio.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libAudio.a"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/Audio && $(CMAKE_COMMAND) -P CMakeFiles/Audio.dir/cmake_clean_target.cmake
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/Audio && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Audio.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Audio/CMakeFiles/Audio.dir/build: src/Audio/libAudio.a

.PHONY : src/Audio/CMakeFiles/Audio.dir/build

src/Audio/CMakeFiles/Audio.dir/requires: src/Audio/CMakeFiles/Audio.dir/playback.cpp.o.requires

.PHONY : src/Audio/CMakeFiles/Audio.dir/requires

src/Audio/CMakeFiles/Audio.dir/clean:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/Audio && $(CMAKE_COMMAND) -P CMakeFiles/Audio.dir/cmake_clean.cmake
.PHONY : src/Audio/CMakeFiles/Audio.dir/clean

src/Audio/CMakeFiles/Audio.dir/depend:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio /home/tashrif/Dev/fidel-musicplayer-cmake/build /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/Audio /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/Audio/CMakeFiles/Audio.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Audio/CMakeFiles/Audio.dir/depend

