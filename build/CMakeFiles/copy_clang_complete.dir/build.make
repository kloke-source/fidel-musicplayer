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

# Utility rule file for copy_clang_complete.

# Include the progress variables for this target.
include CMakeFiles/copy_clang_complete.dir/progress.make

CMakeFiles/copy_clang_complete:
	/usr/bin/cmake -DSOURCE_DIR=/home/tashrif/Development/fidel-musicplayer -P /home/tashrif/Development/fidel-musicplayer/copy_clang_complete_files.cmake

copy_clang_complete: CMakeFiles/copy_clang_complete
copy_clang_complete: CMakeFiles/copy_clang_complete.dir/build.make

.PHONY : copy_clang_complete

# Rule to build all files generated by this target.
CMakeFiles/copy_clang_complete.dir/build: copy_clang_complete

.PHONY : CMakeFiles/copy_clang_complete.dir/build

CMakeFiles/copy_clang_complete.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/copy_clang_complete.dir/cmake_clean.cmake
.PHONY : CMakeFiles/copy_clang_complete.dir/clean

CMakeFiles/copy_clang_complete.dir/depend:
	cd /home/tashrif/Development/fidel-musicplayer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tashrif/Development/fidel-musicplayer /home/tashrif/Development/fidel-musicplayer /home/tashrif/Development/fidel-musicplayer/build /home/tashrif/Development/fidel-musicplayer/build /home/tashrif/Development/fidel-musicplayer/build/CMakeFiles/copy_clang_complete.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/copy_clang_complete.dir/depend

