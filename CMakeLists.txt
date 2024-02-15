# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name and language
project(timespec_library CXX)

# Set the source and build directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Library configuration
add_library(timespec
    ${LIB_DIR}/timespec.h
    ${LIB_DIR}/timespec.cpp
)

add_library(timer
    ${LIB_DIR}/timer.h
    ${LIB_DIR}/timer.cpp
)

add_library(posix_thread
    ${LIB_DIR}/posix_thread.h
    ${LIB_DIR}/posix_thread.cpp
)

add_library(thread
    ${LIB_DIR}/thread.h
    ${LIB_DIR}/thread.cpp
)

add_library(mutex
    ${LIB_DIR}/mutex.h
    ${LIB_DIR}/mutex.cpp
)

# Test file configuration
add_executable(test_timespec
    ${LIB_DIR}/test_timespec.cpp
)

add_executable(test_pthread
    ${LIB_DIR}/test_pthread.cpp
)

add_executable(test_timer
    ${LIB_DIR}/test_timer.cpp
)

add_executable(test_classpthread
    ${LIB_DIR}/test_classpthread.cpp
)

add_executable(test_mutex
    ${LIB_DIR}/test_mutex.cpp
)

# Link the library to the test executable
target_link_libraries(test_timespec timespec timer)
target_link_libraries(test_timer timespec timer)
target_link_libraries(test_pthread timespec pthread)
target_link_libraries(test_classpthread timespec pthread posix_thread thread)
target_link_libraries(test_mutex timespec pthread posix_thread thread mutex)

target_link_libraries(timer PUBLIC timespec PRIVATE rt)


# Add the library directory to the include path
target_include_directories(timespec PUBLIC ${LIB_DIR})
target_include_directories(timer PUBLIC ${LIB_DIR})
target_include_directories(posix_thread PUBLIC ${LIB_DIR})
target_include_directories(thread PUBLIC ${LIB_DIR})
target_include_directories(mutex PUBLIC ${LIB_DIR})

# Add the library directory to the test include path
target_include_directories(test_timespec PRIVATE ${LIB_DIR})
target_include_directories(test_timer PRIVATE ${LIB_DIR})
target_include_directories(test_pthread PRIVATE ${LIB_DIR})
target_include_directories(test_classpthread PRIVATE ${LIB_DIR})
target_include_directories(test_mutex PRIVATE ${LIB_DIR})

# Set the output directories for the library and test executable
set_target_properties(timespec PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(timer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(posix_thread PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(thread PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(mutex PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

set_target_properties(test_timespec PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(test_timer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(test_pthread PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(test_classpthread PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(test_mutex PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
