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
CMAKE_SOURCE_DIR = /home/usaurio/Left4Dead

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/usaurio/Left4Dead/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/client_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/client_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/client_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/client_tests.dir/flags.make

tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o: tests/CMakeFiles/client_tests.dir/flags.make
tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o: ../tests/client_tests/client_protocol_tests.cpp
tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o: tests/CMakeFiles/client_tests.dir/compiler_depend.ts
<<<<<<< HEAD
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usaurio/Left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o -MF CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o.d -o CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o -c /home/usaurio/Left4Dead/tests/client_tests/client_protocol_tests.cpp

tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.i"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usaurio/Left4Dead/tests/client_tests/client_protocol_tests.cpp > CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.i

tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.s"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usaurio/Left4Dead/tests/client_tests/client_protocol_tests.cpp -o CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.s
=======
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o -MF CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o.d -o CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o -c /home/regman/taller/left4Dead/tests/client_tests/client_protocol_tests.cpp

tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.i"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/regman/taller/left4Dead/tests/client_tests/client_protocol_tests.cpp > CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.i

tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.s"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/regman/taller/left4Dead/tests/client_tests/client_protocol_tests.cpp -o CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.s
>>>>>>> caba5539a9f81d9d1019d0417356e71acfbba203

tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o: tests/CMakeFiles/client_tests.dir/flags.make
tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o: ../tests/client_tests/main_client_test.cpp
tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o: tests/CMakeFiles/client_tests.dir/compiler_depend.ts
<<<<<<< HEAD
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usaurio/Left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o -MF CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o.d -o CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o -c /home/usaurio/Left4Dead/tests/client_tests/main_client_test.cpp

tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.i"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usaurio/Left4Dead/tests/client_tests/main_client_test.cpp > CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.i

tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.s"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usaurio/Left4Dead/tests/client_tests/main_client_test.cpp -o CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.s
=======
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o -MF CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o.d -o CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o -c /home/regman/taller/left4Dead/tests/client_tests/main_client_test.cpp

tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.i"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/regman/taller/left4Dead/tests/client_tests/main_client_test.cpp > CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.i

tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.s"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/regman/taller/left4Dead/tests/client_tests/main_client_test.cpp -o CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.s
>>>>>>> caba5539a9f81d9d1019d0417356e71acfbba203

tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o: tests/CMakeFiles/client_tests.dir/flags.make
tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o: ../dipa_classes/resolver.cpp
tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o: tests/CMakeFiles/client_tests.dir/compiler_depend.ts
<<<<<<< HEAD
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usaurio/Left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o -MF CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o.d -o CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o -c /home/usaurio/Left4Dead/dipa_classes/resolver.cpp

tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.i"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usaurio/Left4Dead/dipa_classes/resolver.cpp > CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.i

tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.s"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usaurio/Left4Dead/dipa_classes/resolver.cpp -o CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.s
=======
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o -MF CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o.d -o CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o -c /home/regman/taller/left4Dead/dipa_classes/resolver.cpp

tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.i"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/regman/taller/left4Dead/dipa_classes/resolver.cpp > CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.i

tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.s"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/regman/taller/left4Dead/dipa_classes/resolver.cpp -o CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.s
>>>>>>> caba5539a9f81d9d1019d0417356e71acfbba203

tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o: tests/CMakeFiles/client_tests.dir/flags.make
tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o: ../dipa_classes/liberror.cpp
tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o: tests/CMakeFiles/client_tests.dir/compiler_depend.ts
<<<<<<< HEAD
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usaurio/Left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o -MF CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o.d -o CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o -c /home/usaurio/Left4Dead/dipa_classes/liberror.cpp

tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.i"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usaurio/Left4Dead/dipa_classes/liberror.cpp > CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.i

tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.s"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usaurio/Left4Dead/dipa_classes/liberror.cpp -o CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.s
=======
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o -MF CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o.d -o CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o -c /home/regman/taller/left4Dead/dipa_classes/liberror.cpp

tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.i"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/regman/taller/left4Dead/dipa_classes/liberror.cpp > CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.i

tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.s"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/regman/taller/left4Dead/dipa_classes/liberror.cpp -o CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.s
>>>>>>> caba5539a9f81d9d1019d0417356e71acfbba203

tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o: tests/CMakeFiles/client_tests.dir/flags.make
tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o: ../dipa_classes/resolvererror.cpp
tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o: tests/CMakeFiles/client_tests.dir/compiler_depend.ts
<<<<<<< HEAD
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usaurio/Left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o -MF CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o.d -o CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o -c /home/usaurio/Left4Dead/dipa_classes/resolvererror.cpp

tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.i"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usaurio/Left4Dead/dipa_classes/resolvererror.cpp > CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.i

tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.s"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usaurio/Left4Dead/dipa_classes/resolvererror.cpp -o CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.s
=======
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o -MF CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o.d -o CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o -c /home/regman/taller/left4Dead/dipa_classes/resolvererror.cpp

tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.i"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/regman/taller/left4Dead/dipa_classes/resolvererror.cpp > CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.i

tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.s"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/regman/taller/left4Dead/dipa_classes/resolvererror.cpp -o CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.s
>>>>>>> caba5539a9f81d9d1019d0417356e71acfbba203

tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o: tests/CMakeFiles/client_tests.dir/flags.make
tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o: ../client/client_connection/client_protocol.cpp
tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o: tests/CMakeFiles/client_tests.dir/compiler_depend.ts
<<<<<<< HEAD
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usaurio/Left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o -MF CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o.d -o CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o -c /home/usaurio/Left4Dead/client/client_connection/client_protocol.cpp

tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.i"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usaurio/Left4Dead/client/client_connection/client_protocol.cpp > CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.i

tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.s"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usaurio/Left4Dead/client/client_connection/client_protocol.cpp -o CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.s
=======
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o -MF CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o.d -o CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o -c /home/regman/taller/left4Dead/client/client_connection/client_protocol.cpp

tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.i"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/regman/taller/left4Dead/client/client_connection/client_protocol.cpp > CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.i

tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.s"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/regman/taller/left4Dead/client/client_connection/client_protocol.cpp -o CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.s
>>>>>>> caba5539a9f81d9d1019d0417356e71acfbba203

tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o: tests/CMakeFiles/client_tests.dir/flags.make
tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o: ../dipa_classes/socket.cpp
tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o: tests/CMakeFiles/client_tests.dir/compiler_depend.ts
<<<<<<< HEAD
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usaurio/Left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o -MF CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o.d -o CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o -c /home/usaurio/Left4Dead/dipa_classes/socket.cpp

tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.i"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usaurio/Left4Dead/dipa_classes/socket.cpp > CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.i

tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.s"
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usaurio/Left4Dead/dipa_classes/socket.cpp -o CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.s
=======
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/regman/taller/left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o -MF CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o.d -o CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o -c /home/regman/taller/left4Dead/dipa_classes/socket.cpp

tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.i"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/regman/taller/left4Dead/dipa_classes/socket.cpp > CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.i

tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.s"
	cd /home/regman/taller/left4Dead/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/regman/taller/left4Dead/dipa_classes/socket.cpp -o CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.s
>>>>>>> caba5539a9f81d9d1019d0417356e71acfbba203

# Object files for target client_tests
client_tests_OBJECTS = \
"CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o" \
"CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o" \
"CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o" \
"CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o" \
"CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o" \
"CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o" \
"CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o"

# External object files for target client_tests
client_tests_EXTERNAL_OBJECTS =

tests/client_tests: tests/CMakeFiles/client_tests.dir/client_tests/client_protocol_tests.cpp.o
tests/client_tests: tests/CMakeFiles/client_tests.dir/client_tests/main_client_test.cpp.o
tests/client_tests: tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolver.cpp.o
tests/client_tests: tests/CMakeFiles/client_tests.dir/__/dipa_classes/liberror.cpp.o
tests/client_tests: tests/CMakeFiles/client_tests.dir/__/dipa_classes/resolvererror.cpp.o
tests/client_tests: tests/CMakeFiles/client_tests.dir/__/client/client_connection/client_protocol.cpp.o
tests/client_tests: tests/CMakeFiles/client_tests.dir/__/dipa_classes/socket.cpp.o
tests/client_tests: tests/CMakeFiles/client_tests.dir/build.make
tests/client_tests: lib/libgtest.a
tests/client_tests: lib/libgtest_main.a
tests/client_tests: lib/libgmock.a
tests/client_tests: lib/libgmock_main.a
tests/client_tests: lib/libgmock.a
tests/client_tests: lib/libgtest.a
tests/client_tests: tests/CMakeFiles/client_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/usaurio/Left4Dead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable client_tests"
	cd /home/usaurio/Left4Dead/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_tests.dir/link.txt --verbose=$(VERBOSE)
	cd /home/usaurio/Left4Dead/build/tests && /usr/bin/cmake -D TEST_TARGET=client_tests -D TEST_EXECUTABLE=/home/usaurio/Left4Dead/build/tests/client_tests -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/usaurio/Left4Dead/build/tests -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=client_tests_TESTS -D CTEST_FILE=/home/usaurio/Left4Dead/build/tests/client_tests[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.22/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
tests/CMakeFiles/client_tests.dir/build: tests/client_tests
.PHONY : tests/CMakeFiles/client_tests.dir/build

tests/CMakeFiles/client_tests.dir/clean:
	cd /home/usaurio/Left4Dead/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/client_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/client_tests.dir/clean

tests/CMakeFiles/client_tests.dir/depend:
	cd /home/usaurio/Left4Dead/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/usaurio/Left4Dead /home/usaurio/Left4Dead/tests /home/usaurio/Left4Dead/build /home/usaurio/Left4Dead/build/tests /home/usaurio/Left4Dead/build/tests/CMakeFiles/client_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/client_tests.dir/depend

