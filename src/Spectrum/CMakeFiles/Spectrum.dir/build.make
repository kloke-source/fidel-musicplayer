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
CMAKE_SOURCE_DIR = /home/tashrif/Dev/fidel-musicplayer-cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tashrif/Dev/fidel-musicplayer-cmake

# Include any dependencies generated for this target.
include src/Spectrum/CMakeFiles/Spectrum.dir/depend.make

# Include the progress variables for this target.
include src/Spectrum/CMakeFiles/Spectrum.dir/progress.make

# Include the compile flags for this target's objects.
include src/Spectrum/CMakeFiles/Spectrum.dir/flags.make

src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o: src/Spectrum/CMakeFiles/Spectrum.dir/flags.make
src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o: src/Spectrum/spectrum.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Spectrum.dir/spectrum.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum/spectrum.cpp

src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Spectrum.dir/spectrum.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum/spectrum.cpp > CMakeFiles/Spectrum.dir/spectrum.cpp.i

src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Spectrum.dir/spectrum.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum/spectrum.cpp -o CMakeFiles/Spectrum.dir/spectrum.cpp.s

src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o.requires:

.PHONY : src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o.requires

src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o.provides: src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o.requires
	$(MAKE) -f src/Spectrum/CMakeFiles/Spectrum.dir/build.make src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o.provides.build
.PHONY : src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o.provides

src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o.provides.build: src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o


# Object files for target Spectrum
Spectrum_OBJECTS = \
"CMakeFiles/Spectrum.dir/spectrum.cpp.o"

# External object files for target Spectrum
Spectrum_EXTERNAL_OBJECTS =

src/Spectrum/libSpectrum_debug.a: src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o
src/Spectrum/libSpectrum_debug.a: src/Spectrum/CMakeFiles/Spectrum.dir/build.make
src/Spectrum/libSpectrum_debug.a: src/Spectrum/CMakeFiles/Spectrum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libSpectrum_debug.a"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum && $(CMAKE_COMMAND) -P CMakeFiles/Spectrum.dir/cmake_clean_target.cmake
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Spectrum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Spectrum/CMakeFiles/Spectrum.dir/build: src/Spectrum/libSpectrum_debug.a

.PHONY : src/Spectrum/CMakeFiles/Spectrum.dir/build

src/Spectrum/CMakeFiles/Spectrum.dir/requires: src/Spectrum/CMakeFiles/Spectrum.dir/spectrum.cpp.o.requires

.PHONY : src/Spectrum/CMakeFiles/Spectrum.dir/requires

src/Spectrum/CMakeFiles/Spectrum.dir/clean:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum && $(CMAKE_COMMAND) -P CMakeFiles/Spectrum.dir/cmake_clean.cmake
.PHONY : src/Spectrum/CMakeFiles/Spectrum.dir/clean

src/Spectrum/CMakeFiles/Spectrum.dir/depend:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum /home/tashrif/Dev/fidel-musicplayer-cmake/src/Spectrum/CMakeFiles/Spectrum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Spectrum/CMakeFiles/Spectrum.dir/depend

