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

src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o: src/GUI/CMakeFiles/GUI.dir/flags.make
src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o: ../src/GUI/fidel-resources.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GUI.dir/fidel-resources.c.o   -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/fidel-resources.c

src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GUI.dir/fidel-resources.c.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/fidel-resources.c > CMakeFiles/GUI.dir/fidel-resources.c.i

src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GUI.dir/fidel-resources.c.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/fidel-resources.c -o CMakeFiles/GUI.dir/fidel-resources.c.s

src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o.requires:

.PHONY : src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o.requires

src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o.provides: src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o.requires
	$(MAKE) -f src/GUI/CMakeFiles/GUI.dir/build.make src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o.provides.build
.PHONY : src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o.provides

src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o.provides.build: src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o


src/GUI/CMakeFiles/GUI.dir/gui.cpp.o: src/GUI/CMakeFiles/GUI.dir/flags.make
src/GUI/CMakeFiles/GUI.dir/gui.cpp.o: ../src/GUI/gui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/GUI/CMakeFiles/GUI.dir/gui.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GUI.dir/gui.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/gui.cpp

src/GUI/CMakeFiles/GUI.dir/gui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GUI.dir/gui.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/gui.cpp > CMakeFiles/GUI.dir/gui.cpp.i

src/GUI/CMakeFiles/GUI.dir/gui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GUI.dir/gui.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/gui.cpp -o CMakeFiles/GUI.dir/gui.cpp.s

src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.requires:

.PHONY : src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.requires

src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.provides: src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.requires
	$(MAKE) -f src/GUI/CMakeFiles/GUI.dir/build.make src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.provides.build
.PHONY : src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.provides

src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.provides.build: src/GUI/CMakeFiles/GUI.dir/gui.cpp.o


src/GUI/CMakeFiles/GUI.dir/themer.cpp.o: src/GUI/CMakeFiles/GUI.dir/flags.make
src/GUI/CMakeFiles/GUI.dir/themer.cpp.o: ../src/GUI/themer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/GUI/CMakeFiles/GUI.dir/themer.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GUI.dir/themer.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/themer.cpp

src/GUI/CMakeFiles/GUI.dir/themer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GUI.dir/themer.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/themer.cpp > CMakeFiles/GUI.dir/themer.cpp.i

src/GUI/CMakeFiles/GUI.dir/themer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GUI.dir/themer.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/themer.cpp -o CMakeFiles/GUI.dir/themer.cpp.s

src/GUI/CMakeFiles/GUI.dir/themer.cpp.o.requires:

.PHONY : src/GUI/CMakeFiles/GUI.dir/themer.cpp.o.requires

src/GUI/CMakeFiles/GUI.dir/themer.cpp.o.provides: src/GUI/CMakeFiles/GUI.dir/themer.cpp.o.requires
	$(MAKE) -f src/GUI/CMakeFiles/GUI.dir/build.make src/GUI/CMakeFiles/GUI.dir/themer.cpp.o.provides.build
.PHONY : src/GUI/CMakeFiles/GUI.dir/themer.cpp.o.provides

src/GUI/CMakeFiles/GUI.dir/themer.cpp.o.provides.build: src/GUI/CMakeFiles/GUI.dir/themer.cpp.o


src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o: src/GUI/CMakeFiles/GUI.dir/flags.make
src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o: ../src/GUI/fidel-popover.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GUI.dir/fidel-popover.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/fidel-popover.cpp

src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GUI.dir/fidel-popover.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/fidel-popover.cpp > CMakeFiles/GUI.dir/fidel-popover.cpp.i

src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GUI.dir/fidel-popover.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/fidel-popover.cpp -o CMakeFiles/GUI.dir/fidel-popover.cpp.s

src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o.requires:

.PHONY : src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o.requires

src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o.provides: src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o.requires
	$(MAKE) -f src/GUI/CMakeFiles/GUI.dir/build.make src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o.provides.build
.PHONY : src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o.provides

src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o.provides.build: src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o


src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o: src/GUI/CMakeFiles/GUI.dir/flags.make
src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o: ../src/GUI/playlist.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GUI.dir/playlist.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/playlist.cpp

src/GUI/CMakeFiles/GUI.dir/playlist.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GUI.dir/playlist.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/playlist.cpp > CMakeFiles/GUI.dir/playlist.cpp.i

src/GUI/CMakeFiles/GUI.dir/playlist.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GUI.dir/playlist.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/playlist.cpp -o CMakeFiles/GUI.dir/playlist.cpp.s

src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o.requires:

.PHONY : src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o.requires

src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o.provides: src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o.requires
	$(MAKE) -f src/GUI/CMakeFiles/GUI.dir/build.make src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o.provides.build
.PHONY : src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o.provides

src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o.provides.build: src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o


src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o: src/GUI/CMakeFiles/GUI.dir/flags.make
src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o: ../src/GUI/seeker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GUI.dir/seeker.cpp.o -c /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/seeker.cpp

src/GUI/CMakeFiles/GUI.dir/seeker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GUI.dir/seeker.cpp.i"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/seeker.cpp > CMakeFiles/GUI.dir/seeker.cpp.i

src/GUI/CMakeFiles/GUI.dir/seeker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GUI.dir/seeker.cpp.s"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI/seeker.cpp -o CMakeFiles/GUI.dir/seeker.cpp.s

src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o.requires:

.PHONY : src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o.requires

src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o.provides: src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o.requires
	$(MAKE) -f src/GUI/CMakeFiles/GUI.dir/build.make src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o.provides.build
.PHONY : src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o.provides

src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o.provides.build: src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o


# Object files for target GUI
GUI_OBJECTS = \
"CMakeFiles/GUI.dir/fidel-resources.c.o" \
"CMakeFiles/GUI.dir/gui.cpp.o" \
"CMakeFiles/GUI.dir/themer.cpp.o" \
"CMakeFiles/GUI.dir/fidel-popover.cpp.o" \
"CMakeFiles/GUI.dir/playlist.cpp.o" \
"CMakeFiles/GUI.dir/seeker.cpp.o"

# External object files for target GUI
GUI_EXTERNAL_OBJECTS =

src/GUI/libGUI_debug.a: src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o
src/GUI/libGUI_debug.a: src/GUI/CMakeFiles/GUI.dir/gui.cpp.o
src/GUI/libGUI_debug.a: src/GUI/CMakeFiles/GUI.dir/themer.cpp.o
src/GUI/libGUI_debug.a: src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o
src/GUI/libGUI_debug.a: src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o
src/GUI/libGUI_debug.a: src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o
src/GUI/libGUI_debug.a: src/GUI/CMakeFiles/GUI.dir/build.make
src/GUI/libGUI_debug.a: src/GUI/CMakeFiles/GUI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tashrif/Dev/fidel-musicplayer-cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libGUI_debug.a"
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && $(CMAKE_COMMAND) -P CMakeFiles/GUI.dir/cmake_clean_target.cmake
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GUI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/GUI/CMakeFiles/GUI.dir/build: src/GUI/libGUI_debug.a

.PHONY : src/GUI/CMakeFiles/GUI.dir/build

src/GUI/CMakeFiles/GUI.dir/requires: src/GUI/CMakeFiles/GUI.dir/fidel-resources.c.o.requires
src/GUI/CMakeFiles/GUI.dir/requires: src/GUI/CMakeFiles/GUI.dir/gui.cpp.o.requires
src/GUI/CMakeFiles/GUI.dir/requires: src/GUI/CMakeFiles/GUI.dir/themer.cpp.o.requires
src/GUI/CMakeFiles/GUI.dir/requires: src/GUI/CMakeFiles/GUI.dir/fidel-popover.cpp.o.requires
src/GUI/CMakeFiles/GUI.dir/requires: src/GUI/CMakeFiles/GUI.dir/playlist.cpp.o.requires
src/GUI/CMakeFiles/GUI.dir/requires: src/GUI/CMakeFiles/GUI.dir/seeker.cpp.o.requires

.PHONY : src/GUI/CMakeFiles/GUI.dir/requires

src/GUI/CMakeFiles/GUI.dir/clean:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI && $(CMAKE_COMMAND) -P CMakeFiles/GUI.dir/cmake_clean.cmake
.PHONY : src/GUI/CMakeFiles/GUI.dir/clean

src/GUI/CMakeFiles/GUI.dir/depend:
	cd /home/tashrif/Dev/fidel-musicplayer-cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tashrif/Dev/fidel-musicplayer-cmake /home/tashrif/Dev/fidel-musicplayer-cmake/src/GUI /home/tashrif/Dev/fidel-musicplayer-cmake/build /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI /home/tashrif/Dev/fidel-musicplayer-cmake/build/src/GUI/CMakeFiles/GUI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/GUI/CMakeFiles/GUI.dir/depend

