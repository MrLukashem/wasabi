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
CMAKE_SOURCE_DIR = /home/lmerta/Projects/wasabi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lmerta/Projects/wasabi/build

# Include any dependencies generated for this target.
include CMakeFiles/wasabiTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wasabiTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wasabiTest.dir/flags.make

CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o: CMakeFiles/wasabiTest.dir/flags.make
CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o: ../tests/AudioBufferTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lmerta/Projects/wasabi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o -c /home/lmerta/Projects/wasabi/tests/AudioBufferTests.cpp

CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lmerta/Projects/wasabi/tests/AudioBufferTests.cpp > CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.i

CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lmerta/Projects/wasabi/tests/AudioBufferTests.cpp -o CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.s

CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o.requires:

.PHONY : CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o.requires

CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o.provides: CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o.requires
	$(MAKE) -f CMakeFiles/wasabiTest.dir/build.make CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o.provides.build
.PHONY : CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o.provides

CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o.provides.build: CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o


CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o: CMakeFiles/wasabiTest.dir/flags.make
CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o: ../tests/TypeWrapperTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lmerta/Projects/wasabi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o -c /home/lmerta/Projects/wasabi/tests/TypeWrapperTests.cpp

CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lmerta/Projects/wasabi/tests/TypeWrapperTests.cpp > CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.i

CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lmerta/Projects/wasabi/tests/TypeWrapperTests.cpp -o CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.s

CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o.requires:

.PHONY : CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o.requires

CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o.provides: CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o.requires
	$(MAKE) -f CMakeFiles/wasabiTest.dir/build.make CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o.provides.build
.PHONY : CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o.provides

CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o.provides.build: CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o


CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o: CMakeFiles/wasabiTest.dir/flags.make
CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o: ../tests/StreamBuilderTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lmerta/Projects/wasabi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o -c /home/lmerta/Projects/wasabi/tests/StreamBuilderTests.cpp

CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lmerta/Projects/wasabi/tests/StreamBuilderTests.cpp > CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.i

CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lmerta/Projects/wasabi/tests/StreamBuilderTests.cpp -o CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.s

CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o.requires:

.PHONY : CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o.requires

CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o.provides: CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o.requires
	$(MAKE) -f CMakeFiles/wasabiTest.dir/build.make CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o.provides.build
.PHONY : CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o.provides

CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o.provides.build: CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o


CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o: CMakeFiles/wasabiTest.dir/flags.make
CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o: ../src/audio/StreamBuilder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lmerta/Projects/wasabi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o -c /home/lmerta/Projects/wasabi/src/audio/StreamBuilder.cpp

CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lmerta/Projects/wasabi/src/audio/StreamBuilder.cpp > CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.i

CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lmerta/Projects/wasabi/src/audio/StreamBuilder.cpp -o CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.s

CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o.requires:

.PHONY : CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o.requires

CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o.provides: CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o.requires
	$(MAKE) -f CMakeFiles/wasabiTest.dir/build.make CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o.provides.build
.PHONY : CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o.provides

CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o.provides.build: CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o


# Object files for target wasabiTest
wasabiTest_OBJECTS = \
"CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o" \
"CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o" \
"CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o" \
"CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o"

# External object files for target wasabiTest
wasabiTest_EXTERNAL_OBJECTS =

wasabiTest: CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o
wasabiTest: CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o
wasabiTest: CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o
wasabiTest: CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o
wasabiTest: CMakeFiles/wasabiTest.dir/build.make
wasabiTest: CMakeFiles/wasabiTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lmerta/Projects/wasabi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable wasabiTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wasabiTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wasabiTest.dir/build: wasabiTest

.PHONY : CMakeFiles/wasabiTest.dir/build

CMakeFiles/wasabiTest.dir/requires: CMakeFiles/wasabiTest.dir/tests/AudioBufferTests.cpp.o.requires
CMakeFiles/wasabiTest.dir/requires: CMakeFiles/wasabiTest.dir/tests/TypeWrapperTests.cpp.o.requires
CMakeFiles/wasabiTest.dir/requires: CMakeFiles/wasabiTest.dir/tests/StreamBuilderTests.cpp.o.requires
CMakeFiles/wasabiTest.dir/requires: CMakeFiles/wasabiTest.dir/src/audio/StreamBuilder.cpp.o.requires

.PHONY : CMakeFiles/wasabiTest.dir/requires

CMakeFiles/wasabiTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wasabiTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wasabiTest.dir/clean

CMakeFiles/wasabiTest.dir/depend:
	cd /home/lmerta/Projects/wasabi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lmerta/Projects/wasabi /home/lmerta/Projects/wasabi /home/lmerta/Projects/wasabi/build /home/lmerta/Projects/wasabi/build /home/lmerta/Projects/wasabi/build/CMakeFiles/wasabiTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wasabiTest.dir/depend

