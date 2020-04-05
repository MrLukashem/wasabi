
cmake_minimum_required(VERSION 3.10)

# set the project name
project(wasabi)

include_directories(
    src/audio/base/include
    tests/include)
# add the executable
add_executable(wasabi src/main.cpp)

# libs for the linker
target_link_libraries(wasabi libasound.so)

add_executable(wasabiTest tests/AudioBufferTests.cpp)
enable_testing()
add_test(NAME wasabiTest COMMAND wasabi)
