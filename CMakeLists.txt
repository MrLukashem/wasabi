
cmake_minimum_required(VERSION 3.10)

# set the project name
project(wasabi)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    src/audio/base/include
    src/audio/include
    tests/include)
# add the executable
add_executable(wasabi
    src/main.cpp
    src/audio/Devices.cpp)

# libs for the linker
target_link_libraries(wasabi libasound.so)
add_executable(wasabiTest
    tests/AudioBufferTests.cpp
    tests/TypeWrapperTests.cpp
    tests/StreamBuilderTests.cpp
    src/audio/Devices.cpp)
enable_testing()
add_test(NAME wasabiTest COMMAND wasabi)
