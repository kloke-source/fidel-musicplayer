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
include src/GUI/CMakeFiles/GUI.dir/depend.make

# Include the progress variables for this target.
include src/GUI/CMakeFiles/GUI.dir/progress.make

# Include the compile flags for this target's objects.
include src/GUI/CMakeFiles/GUI.dir/flags.make

src/GUI/CMakeFiles/GUI.dir/gui.cpp.o: src/GUI/CMakeFiles/GUI.dir/flags.make
src/GUI/CMakeFiles/GUI.dir/gui.cpp.o: ../src/GUI/gui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/GUI/CMakeFiles/GUI.dir/gui.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/lib/hardening-wrapper/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GUI.dir/gui.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/gui.cpp

src/GUI/CMakeFiles/GUI.dir/gui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GUI.dir/gui.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/lib/hardening-wrapper/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/gui.cpp > CMakeFiles/GUI.dir/gui.cpp.i

src/GUI/CMakeFiles/GUI.dir/gui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GUI.dir/gui.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/lib/hardening-wrapper/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/gui.cpp -o CMakeFiles/GUI.dir/gui.cpp.s

src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.requires:

.PHONY : src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.requires

src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.provides: src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.requires
	$(MAKE) -f src/GUI/CMakeFiles/GUI.dir/build.make src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.provides.build
.PHONY : src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.provides

src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.provides.build: src/GUI/CMakeFiles/GUI.dir/gui.cpp.o


src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o: src/GUI/CMakeFiles/GUI.dir/flags.make
src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o: ../src/GUI/fidel-resources.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/lib/hardening-wrapper/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GUI.dir/fidel-resources.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/fidel-resources.cpp

src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GUI.dir/fidel-resources.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/lib/hardening-wrapper/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/fidel-resources.cpp > CMakeFiles/GUI.dir/fidel-resources.cpp.i

src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GUI.dir/fidel-resources.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/lib/hardening-wrapper/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/fidel-resources.cpp -o CMakeFiles/GUI.dir/fidel-resources.cpp.s

src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o.requires:

.PHONY : src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o.requires

src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o.provides: src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o.requires
	$(MAKE) -f src/GUI/CMakeFiles/GUI.dir/build.make src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o.provides.build
.PHONY : src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o.provides

src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o.provides.build: src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o


# Object files for target GUI
GUI_OBJECTS = \
"CMakeFiles/GUI.dir/gui.cpp.o" \
"CMakeFiles/GUI.dir/fidel-resources.cpp.o"

# External object files for target GUI
GUI_EXTERNAL_OBJECTS =

src/GUI/libGUI.a: src/GUI/CMakeFiles/GUI.dir/gui.cpp.o
src/GUI/libGUI.a: src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o
src/GUI/libGUI.a: src/GUI/CMakeFiles/GUI.dir/build.make
src/GUI/libGUI.a: src/GUI/CMakeFiles/GUI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libGUI.a"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && $(CMAKE_COMMAND) -P CMakeFiles/GUI.dir/cmake_clean_target.cmake
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GUI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/GUI/CMakeFiles/GUI.dir/build: src/GUI/libGUI.a

.PHONY : src/GUI/CMakeFiles/GUI.dir/build

src/GUI/CMakeFiles/GUI.dir/requires: src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.requires
src/GUI/CMakeFiles/GUI.dir/requires: src/GUI/CMakeFiles/GUI.dir/fidel-resources.cpp.o.requires

.PHONY : src/GUI/CMakeFiles/GUI.dir/requires

src/GUI/CMakeFiles/GUI.dir/clean:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && $(CMAKE_COMMAND) -P CMakeFiles/GUI.dir/cmake_clean.cmake
.PHONY : src/GUI/CMakeFiles/GUI.dir/clean

src/GUI/CMakeFiles/GUI.dir/depend:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI /home/tashrif/Dev/fidel-musicplayer-cmake/build /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI/CMakeFiles/GUI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/GUI/CMakeFiles/GUI.dir/depend

