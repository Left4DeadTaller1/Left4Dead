# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/regman/taller/left4Dead

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/regman/taller/left4Dead/build

# Include any dependencies generated for this target.
include CMakeFiles/qt.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/qt.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qt.dir/flags.make

ui_mainwindow.h: ../mainwindow.ui
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ui_mainwindow.h"
	/usr/lib/qt5/bin/uic -o /home/regman/taller/left4Dead/build/ui_mainwindow.h /home/regman/taller/left4Dead/mainwindow.ui

CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.o: CMakeFiles/qt.dir/flags.make
CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.o: qt_autogen/mocs_compilation.cpp
CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.o: CMakeFiles/qt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.o -MF CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.o -c /home/regman/taller/left4Dead/build/qt_autogen/mocs_compilation.cpp

CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/regman/taller/left4Dead/build/qt_autogen/mocs_compilation.cpp > CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.i

CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/regman/taller/left4Dead/build/qt_autogen/mocs_compilation.cpp -o CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.s

CMakeFiles/qt.dir/mainwindow.cpp.o: CMakeFiles/qt.dir/flags.make
CMakeFiles/qt.dir/mainwindow.cpp.o: ../mainwindow.cpp
CMakeFiles/qt.dir/mainwindow.cpp.o: CMakeFiles/qt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/qt.dir/mainwindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt.dir/mainwindow.cpp.o -MF CMakeFiles/qt.dir/mainwindow.cpp.o.d -o CMakeFiles/qt.dir/mainwindow.cpp.o -c /home/regman/taller/left4Dead/mainwindow.cpp

CMakeFiles/qt.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt.dir/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/regman/taller/left4Dead/mainwindow.cpp > CMakeFiles/qt.dir/mainwindow.cpp.i

CMakeFiles/qt.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt.dir/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/regman/taller/left4Dead/mainwindow.cpp -o CMakeFiles/qt.dir/mainwindow.cpp.s

# Object files for target qt
qt_OBJECTS = \
"CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/qt.dir/mainwindow.cpp.o"

# External object files for target qt
qt_EXTERNAL_OBJECTS =

libqt.a: CMakeFiles/qt.dir/qt_autogen/mocs_compilation.cpp.o
libqt.a: CMakeFiles/qt.dir/mainwindow.cpp.o
libqt.a: CMakeFiles/qt.dir/build.make
libqt.a: CMakeFiles/qt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libqt.a"
	$(CMAKE_COMMAND) -P CMakeFiles/qt.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qt.dir/build: libqt.a
.PHONY : CMakeFiles/qt.dir/build

CMakeFiles/qt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qt.dir/clean

CMakeFiles/qt.dir/depend: ui_mainwindow.h
	cd /home/regman/taller/left4Dead/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/regman/taller/left4Dead /home/regman/taller/left4Dead /home/regman/taller/left4Dead/build /home/regman/taller/left4Dead/build /home/regman/taller/left4Dead/build/CMakeFiles/qt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qt.dir/depend

