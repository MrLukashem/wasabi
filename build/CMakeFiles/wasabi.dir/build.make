# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/ryu/Projects/wasabi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ryu/Projects/wasabi/build

# Include any dependencies generated for this target.
include CMakeFiles/wasabi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wasabi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wasabi.dir/flags.make

CMakeFiles/wasabi.dir/src/main.cpp.o: CMakeFiles/wasabi.dir/flags.make
CMakeFiles/wasabi.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ryu/Projects/wasabi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wasabi.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wasabi.dir/src/main.cpp.o -c /home/ryu/Projects/wasabi/src/main.cpp

CMakeFiles/wasabi.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wasabi.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ryu/Projects/wasabi/src/main.cpp > CMakeFiles/wasabi.dir/src/main.cpp.i

CMakeFiles/wasabi.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wasabi.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ryu/Projects/wasabi/src/main.cpp -o CMakeFiles/wasabi.dir/src/main.cpp.s

CMakeFiles/wasabi.dir/src/audio/Devices.cpp.o: CMakeFiles/wasabi.dir/flags.make
CMakeFiles/wasabi.dir/src/audio/Devices.cpp.o: ../src/audio/Devices.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ryu/Projects/wasabi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wasabi.dir/src/audio/Devices.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wasabi.dir/src/audio/Devices.cpp.o -c /home/ryu/Projects/wasabi/src/audio/Devices.cpp

CMakeFiles/wasabi.dir/src/audio/Devices.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wasabi.dir/src/audio/Devices.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ryu/Projects/wasabi/src/audio/Devices.cpp > CMakeFiles/wasabi.dir/src/audio/Devices.cpp.i

CMakeFiles/wasabi.dir/src/audio/Devices.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wasabi.dir/src/audio/Devices.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ryu/Projects/wasabi/src/audio/Devices.cpp -o CMakeFiles/wasabi.dir/src/audio/Devices.cpp.s

# Object files for target wasabi
wasabi_OBJECTS = \
"CMakeFiles/wasabi.dir/src/main.cpp.o" \
"CMakeFiles/wasabi.dir/src/audio/Devices.cpp.o"

# External object files for target wasabi
wasabi_EXTERNAL_OBJECTS =

wasabi: CMakeFiles/wasabi.dir/src/main.cpp.o
wasabi: CMakeFiles/wasabi.dir/src/audio/Devices.cpp.o
wasabi: CMakeFiles/wasabi.dir/build.make
wasabi: CMakeFiles/wasabi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ryu/Projects/wasabi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable wasabi"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wasabi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wasabi.dir/build: wasabi

.PHONY : CMakeFiles/wasabi.dir/build

CMakeFiles/wasabi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wasabi.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wasabi.dir/clean

CMakeFiles/wasabi.dir/depend:
	cd /home/ryu/Projects/wasabi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ryu/Projects/wasabi /home/ryu/Projects/wasabi /home/ryu/Projects/wasabi/build /home/ryu/Projects/wasabi/build /home/ryu/Projects/wasabi/build/CMakeFiles/wasabi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wasabi.dir/depend

