# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
include src/CMakeFiles/fidel.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/fidel.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/fidel.dir/flags.make

src/CMakeFiles/fidel.dir/main.cpp.o: src/CMakeFiles/fidel.dir/flags.make
src/CMakeFiles/fidel.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Development/fidel-musicplayer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/fidel.dir/main.cpp.o"
	cd /home/tashrif/Development/fidel-musicplayer/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fidel.dir/main.cpp.o -c /home/tashrif/Development/fidel-musicplayer/src/main.cpp

src/CMakeFiles/fidel.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fidel.dir/main.cpp.i"
	cd /home/tashrif/Development/fidel-musicplayer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Development/fidel-musicplayer/src/main.cpp > CMakeFiles/fidel.dir/main.cpp.i

src/CMakeFiles/fidel.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fidel.dir/main.cpp.s"
	cd /home/tashrif/Development/fidel-musicplayer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Development/fidel-musicplayer/src/main.cpp -o CMakeFiles/fidel.dir/main.cpp.s

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

../fidel: src/CMakeFiles/fidel.dir/main.cpp.o
../fidel: src/CMakeFiles/fidel.dir/build.make
../fidel: src/GUI/libGUI.a
../fidel: src/Audio-Library/libAudio-Library.a
../fidel: src/Audio/libAudio.a
../fidel: src/Audio-Info/libAudio-Info.a
../fidel: src/Utilities/libUtilities.a
../fidel: src/Spectrum/libSpectrum.a
../fidel: src/CMakeFiles/fidel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tashrif/Development/fidel-musicplayer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../fidel"
	cd /home/tashrif/Development/fidel-musicplayer/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fidel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/fidel.dir/build: ../fidel

.PHONY : src/CMakeFiles/fidel.dir/build

src/CMakeFiles/fidel.dir/requires: src/CMakeFiles/fidel.dir/main.cpp.o.requires

.PHONY : src/CMakeFiles/fidel.dir/requires

src/CMakeFiles/fidel.dir/clean:
	cd /home/tashrif/Development/fidel-musicplayer/build/src && $(CMAKE_COMMAND) -P CMakeFiles/fidel.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/fidel.dir/clean

src/CMakeFiles/fidel.dir/depend:
	cd /home/tashrif/Development/fidel-musicplayer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tashrif/Development/fidel-musicplayer /home/tashrif/Development/fidel-musicplayer/src /home/tashrif/Development/fidel-musicplayer/build /home/tashrif/Development/fidel-musicplayer/build/src /home/tashrif/Development/fidel-musicplayer/build/src/CMakeFiles/fidel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/fidel.dir/depend

