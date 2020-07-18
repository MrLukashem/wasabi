
cmake_minimum_required(VERSION 3.10)

# set the project name
project(wasabi)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DALSA_SUPPORTED=1)

include_directories(
    src/audio/base/include
    src/audio/drivers/include
    src/audio/include
    tests/include
    tests/mocks)
# add the executable
add_executable(wasabi
    src/main.cpp
    src/audio/Devices.cpp
    src/audio/AudioPlaybackStream.cpp
    src/audio/drivers/ASoundAudioDriver.cpp)

# libs for the linker
target_link_libraries(wasabi libasound.so)

add_executable(wasabiTest
    tests/AudioBufferTests.cpp
    tests/AudioPlaybackStreamTests.cpp
    tests/TypeWrapperTests.cpp
    tests/StreamBuilderTests.cpp
    src/audio/Devices.cpp
    src/audio/AudioPlaybackStream.cpp
    src/audio/drivers/ASoundAudioDriver.cpp)
enable_testing()

target_link_libraries(wasabiTest gtest_main.a)
target_link_libraries(wasabiTest gmock.a)
target_link_libraries(wasabiTest gtest.a)
target_link_libraries(wasabiTest pthread.a)

add_test(NAME wasabiTest COMMAND wasabi)
