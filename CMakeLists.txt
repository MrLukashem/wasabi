
cmake_minimum_required(VERSION 3.10)

# set the project name
project(wasabi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

if(NOT TARGET spdlog)
    # Stand-alone build
    add_subdirectory(${CMAKE_SOURCE_DIR}/externals/spdlog)
    #find_package(spdlog REQUIRED PATHS ${CMAKE_SOURCE_DIR}/externals/spdlog NO_DEFAULT_PATH)
endif()

add_definitions(-DALSA_SUPPORTED=1)

include_directories(
    src/audio/base/include
    src/audio/drivers/include
    src/audio/include
    src/audio/utils/include
    tests/include
    tests/mocks
    externals/spdlog/include)
# add the executable
add_executable(wasabi
    src/main.cpp
    src/audio/Devices.cpp
    src/audio/AudioPlaybackStream.cpp
    src/audio/WasabiAudio.cpp
    src/audio/drivers/ASoundAudioDriver.cpp
    src/audio/utils/DeviceCapabilitiesProviders.cpp
)

# libs for the linker
target_link_libraries(wasabi libasound.so)
#target_link_libraries(wasabi PRIVATE spdlog::spdlog)

add_executable(wasabiTest
    tests/AudioBufferTests.cpp
    tests/AudioPlaybackStreamTests.cpp
    tests/ASoundDriverTests.cpp
    tests/TypeWrapperTests.cpp
    tests/StreamBuilderTests.cpp
    tests/DeviceCapabilitiesProvidersTests.cpp
    src/audio/Devices.cpp
    src/audio/AudioPlaybackStream.cpp
    src/audio/drivers/ASoundAudioDriver.cpp
    src/audio/utils/DeviceCapabilitiesProviders.cpp
)

enable_testing()

target_link_libraries(wasabiTest libasound.so)
target_link_libraries(wasabiTest gtest_main.a)
target_link_libraries(wasabiTest gmock.a)
target_link_libraries(wasabiTest gtest.a)

find_package(Threads REQUIRED)
target_link_libraries(wasabiTest Threads::Threads)

add_test(NAME wasabiTest COMMAND wasabi)
