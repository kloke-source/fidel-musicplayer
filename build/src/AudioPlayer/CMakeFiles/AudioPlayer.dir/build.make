# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/tashrif/Development/fidel-musicplayer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tashrif/Development/fidel-musicplayer/build

# Include any dependencies generated for this target.
include src/AudioPlayer/CMakeFiles/AudioPlayer.dir/depend.make

# Include the progress variables for this target.
include src/AudioPlayer/CMakeFiles/AudioPlayer.dir/progress.make

# Include the compile flags for this target's objects.
include src/AudioPlayer/CMakeFiles/AudioPlayer.dir/flags.make

src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o: src/AudioPlayer/CMakeFiles/AudioPlayer.dir/flags.make
src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o: ../src/AudioPlayer/audioplayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Development/fidel-musicplayer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o"
	cd /home/tashrif/Development/fidel-musicplayer/build/src/AudioPlayer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o -c /home/tashrif/Development/fidel-musicplayer/src/AudioPlayer/audioplayer.cpp

src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AudioPlayer.dir/audioplayer.cpp.i"
	cd /home/tashrif/Development/fidel-musicplayer/build/src/AudioPlayer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Development/fidel-musicplayer/src/AudioPlayer/audioplayer.cpp > CMakeFiles/AudioPlayer.dir/audioplayer.cpp.i

src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AudioPlayer.dir/audioplayer.cpp.s"
	cd /home/tashrif/Development/fidel-musicplayer/build/src/AudioPlayer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Development/fidel-musicplayer/src/AudioPlayer/audioplayer.cpp -o CMakeFiles/AudioPlayer.dir/audioplayer.cpp.s

src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o.requires:

.PHONY : src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o.requires

src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o.provides: src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o.requires
	$(MAKE) -f src/AudioPlayer/CMakeFiles/AudioPlayer.dir/build.make src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o.provides.build
.PHONY : src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o.provides

src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o.provides.build: src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o


# Object files for target AudioPlayer
AudioPlayer_OBJECTS = \
"CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o"

# External object files for target AudioPlayer
AudioPlayer_EXTERNAL_OBJECTS =

src/AudioPlayer/libAudioPlayer.a: src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o
src/AudioPlayer/libAudioPlayer.a: src/AudioPlayer/CMakeFiles/AudioPlayer.dir/build.make
src/AudioPlayer/libAudioPlayer.a: src/AudioPlayer/CMakeFiles/AudioPlayer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tashrif/Development/fidel-musicplayer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libAudioPlayer.a"
	cd /home/tashrif/Development/fidel-musicplayer/build/src/AudioPlayer && $(CMAKE_COMMAND) -P CMakeFiles/AudioPlayer.dir/cmake_clean_target.cmake
	cd /home/tashrif/Development/fidel-musicplayer/build/src/AudioPlayer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AudioPlayer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/AudioPlayer/CMakeFiles/AudioPlayer.dir/build: src/AudioPlayer/libAudioPlayer.a

.PHONY : src/AudioPlayer/CMakeFiles/AudioPlayer.dir/build

src/AudioPlayer/CMakeFiles/AudioPlayer.dir/requires: src/AudioPlayer/CMakeFiles/AudioPlayer.dir/audioplayer.cpp.o.requires

.PHONY : src/AudioPlayer/CMakeFiles/AudioPlayer.dir/requires

src/AudioPlayer/CMakeFiles/AudioPlayer.dir/clean:
	cd /home/tashrif/Development/fidel-musicplayer/build/src/AudioPlayer && $(CMAKE_COMMAND) -P CMakeFiles/AudioPlayer.dir/cmake_clean.cmake
.PHONY : src/AudioPlayer/CMakeFiles/AudioPlayer.dir/clean

src/AudioPlayer/CMakeFiles/AudioPlayer.dir/depend:
	cd /home/tashrif/Development/fidel-musicplayer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tashrif/Development/fidel-musicplayer /home/tashrif/Development/fidel-musicplayer/src/AudioPlayer /home/tashrif/Development/fidel-musicplayer/build /home/tashrif/Development/fidel-musicplayer/build/src/AudioPlayer /home/tashrif/Development/fidel-musicplayer/build/src/AudioPlayer/CMakeFiles/AudioPlayer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/AudioPlayer/CMakeFiles/AudioPlayer.dir/depend

