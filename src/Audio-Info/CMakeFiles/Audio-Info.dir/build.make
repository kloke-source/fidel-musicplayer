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
include src/Audio-Info/CMakeFiles/Audio-Info.dir/depend.make

# Include the progress variables for this target.
include src/Audio-Info/CMakeFiles/Audio-Info.dir/progress.make

# Include the compile flags for this target's objects.
include src/Audio-Info/CMakeFiles/Audio-Info.dir/flags.make

src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o: src/Audio-Info/CMakeFiles/Audio-Info.dir/flags.make
src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o: src/Audio-Info/audioinfo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Audio-Info.dir/audioinfo.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info/audioinfo.cpp

src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Audio-Info.dir/audioinfo.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info/audioinfo.cpp > CMakeFiles/Audio-Info.dir/audioinfo.cpp.i

src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Audio-Info.dir/audioinfo.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info/audioinfo.cpp -o CMakeFiles/Audio-Info.dir/audioinfo.cpp.s

src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o.requires:

.PHONY : src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o.requires

src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o.provides: src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o.requires
	$(MAKE) -f src/Audio-Info/CMakeFiles/Audio-Info.dir/build.make src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o.provides.build
.PHONY : src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o.provides

src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o.provides.build: src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o


# Object files for target Audio-Info
Audio__Info_OBJECTS = \
"CMakeFiles/Audio-Info.dir/audioinfo.cpp.o"

# External object files for target Audio-Info
Audio__Info_EXTERNAL_OBJECTS =

src/Audio-Info/libAudio-Info.a: src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o
src/Audio-Info/libAudio-Info.a: src/Audio-Info/CMakeFiles/Audio-Info.dir/build.make
src/Audio-Info/libAudio-Info.a: src/Audio-Info/CMakeFiles/Audio-Info.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libAudio-Info.a"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info && $(CMAKE_COMMAND) -P CMakeFiles/Audio-Info.dir/cmake_clean_target.cmake
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Audio-Info.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Audio-Info/CMakeFiles/Audio-Info.dir/build: src/Audio-Info/libAudio-Info.a

.PHONY : src/Audio-Info/CMakeFiles/Audio-Info.dir/build

src/Audio-Info/CMakeFiles/Audio-Info.dir/requires: src/Audio-Info/CMakeFiles/Audio-Info.dir/audioinfo.cpp.o.requires

.PHONY : src/Audio-Info/CMakeFiles/Audio-Info.dir/requires

src/Audio-Info/CMakeFiles/Audio-Info.dir/clean:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info && $(CMAKE_COMMAND) -P CMakeFiles/Audio-Info.dir/cmake_clean.cmake
.PHONY : src/Audio-Info/CMakeFiles/Audio-Info.dir/clean

src/Audio-Info/CMakeFiles/Audio-Info.dir/depend:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info /home/tashrif/Dev/fidel-musicplayer-cmake/src/Audio-Info/CMakeFiles/Audio-Info.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Audio-Info/CMakeFiles/Audio-Info.dir/depend

