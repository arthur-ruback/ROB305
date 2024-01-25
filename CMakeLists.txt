# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name and language
project(timespec_library CXX)

# Set the source and build directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Library configuration
add_library(timespec
    ${LIB_DIR}/timespec.h
    ${LIB_DIR}/timespec.cpp
)

add_library(chrono
    ${LIB_DIR}/chrono.h
    ${LIB_DIR}/chrono.cpp
)

# Test file configuration
add_executable(test_timespec
    ${LIB_DIR}/test_timespec.cpp
)

# Link the library to the test executable
target_link_libraries(test_timespec PRIVATE timespec)

target_link_libraries(test_timespec PRIVATE chrono)

# Add the library directory to the include path
target_include_directories(timespec PUBLIC ${LIB_DIR})
target_include_directories(chrono PUBLIC ${LIB_DIR})

# Add the library directory to the test include path
target_include_directories(test_timespec PRIVATE ${LIB_DIR})

# Set the output directories for the library and test executable
set_target_properties(timespec PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(test_timespec PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

# Google Test configuration (replace with your test framework if different)
# Assumes that you have Google Test installed on your system
find_package(GTest REQUIRED)
target_link_libraries(test_timespec PRIVATE GTest::GTest GTest::Main)

# Add a test command (optional)
enable_testing()
add_test(NAME test_timespec COMMAND test_timespec)
