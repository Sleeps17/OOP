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
CMAKE_SOURCE_DIR = /home/pasha/Study/OOP/lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pasha/Study/OOP/lab1/build

# Include any dependencies generated for this target.
include CMakeFiles/lab1_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab1_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab1_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab1_test.dir/flags.make

CMakeFiles/lab1_test.dir/test/test_count.cpp.o: CMakeFiles/lab1_test.dir/flags.make
CMakeFiles/lab1_test.dir/test/test_count.cpp.o: ../test/test_count.cpp
CMakeFiles/lab1_test.dir/test/test_count.cpp.o: CMakeFiles/lab1_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pasha/Study/OOP/lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab1_test.dir/test/test_count.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab1_test.dir/test/test_count.cpp.o -MF CMakeFiles/lab1_test.dir/test/test_count.cpp.o.d -o CMakeFiles/lab1_test.dir/test/test_count.cpp.o -c /home/pasha/Study/OOP/lab1/test/test_count.cpp

CMakeFiles/lab1_test.dir/test/test_count.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab1_test.dir/test/test_count.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pasha/Study/OOP/lab1/test/test_count.cpp > CMakeFiles/lab1_test.dir/test/test_count.cpp.i

CMakeFiles/lab1_test.dir/test/test_count.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab1_test.dir/test/test_count.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pasha/Study/OOP/lab1/test/test_count.cpp -o CMakeFiles/lab1_test.dir/test/test_count.cpp.s

# Object files for target lab1_test
lab1_test_OBJECTS = \
"CMakeFiles/lab1_test.dir/test/test_count.cpp.o"

# External object files for target lab1_test
lab1_test_EXTERNAL_OBJECTS =

lab1_test: CMakeFiles/lab1_test.dir/test/test_count.cpp.o
lab1_test: CMakeFiles/lab1_test.dir/build.make
lab1_test: liblab1_lib.a
lab1_test: CMakeFiles/lab1_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pasha/Study/OOP/lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab1_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab1_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab1_test.dir/build: lab1_test
.PHONY : CMakeFiles/lab1_test.dir/build

CMakeFiles/lab1_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab1_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab1_test.dir/clean

CMakeFiles/lab1_test.dir/depend:
	cd /home/pasha/Study/OOP/lab1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pasha/Study/OOP/lab1 /home/pasha/Study/OOP/lab1 /home/pasha/Study/OOP/lab1/build /home/pasha/Study/OOP/lab1/build /home/pasha/Study/OOP/lab1/build/CMakeFiles/lab1_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab1_test.dir/depend

