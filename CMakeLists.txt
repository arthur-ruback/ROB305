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

add_library(semaphore
    ${LIB_DIR}/semaphore.h
    ${LIB_DIR}/semaphore.cpp
)

add_library(chrono
    ${LIB_DIR}/chrono.h
    ${LIB_DIR}/chrono.cpp
)

add_library(cpu_loop
    ${LIB_DIR}/cpu_loop.h
    ${LIB_DIR}/cpu_loop.cpp
)

# Test file configuration
add_executable(TP1-ABC
    ${LIB_DIR}/TP1-ABC.cpp
)

add_executable(TP2
    ${LIB_DIR}/TP2.cpp
)

add_executable(TP3-B
    ${LIB_DIR}/TP3-B.cpp
)

add_executable(TP4-A
    ${LIB_DIR}/TP4-A.cpp
)

add_executable(TP4-B
    ${LIB_DIR}/TP4-B.cpp
)

add_executable(TP4-C
    ${LIB_DIR}/TP4-C.cpp
)

add_executable(TP3-A
    ${LIB_DIR}/TP3-A.cpp
)

add_executable(TP3-C
    ${LIB_DIR}/TP3-C.cpp
)

add_executable(TP5
    ${LIB_DIR}/TP5.cpp
)

# Link the library to the test executable
target_link_libraries(TP1-ABC timespec timer)
target_link_libraries(TP3-B timespec timer)
target_link_libraries(TP2 timespec pthread)
target_link_libraries(TP4-A timespec pthread posix_thread thread)
target_link_libraries(TP4-B timespec pthread posix_thread thread mutex)
target_link_libraries(TP4-C timespec pthread posix_thread thread mutex semaphore)
target_link_libraries(TP3-A timespec chrono)
target_link_libraries(TP3-C cpu_loop)
target_link_libraries(TP5 cpu_loop thread mutex posix_thread timespec chrono)

target_link_libraries(timer PUBLIC timespec PRIVATE rt)
target_link_libraries(posix_thread PUBLIC timespec PRIVATE pthread)
target_link_libraries(semaphore PRIVATE thread mutex)
target_link_libraries(chrono PRIVATE timespec)
target_link_libraries(cpu_loop PRIVATE timer)

# Add the library directory to the include path
target_include_directories(timespec PUBLIC ${LIB_DIR})
target_include_directories(timer PUBLIC ${LIB_DIR})
target_include_directories(posix_thread PUBLIC ${LIB_DIR})
target_include_directories(thread PUBLIC ${LIB_DIR})
target_include_directories(mutex PUBLIC ${LIB_DIR})
target_include_directories(semaphore PUBLIC ${LIB_DIR})
target_include_directories(chrono PUBLIC ${LIB_DIR})
target_include_directories(cpu_loop PUBLIC ${LIB_DIR})

# Add the library directory to the test include path
target_include_directories(TP1-ABC PRIVATE ${LIB_DIR})
target_include_directories(TP3-B PRIVATE ${LIB_DIR})
target_include_directories(TP2 PRIVATE ${LIB_DIR})
target_include_directories(TP4-A PRIVATE ${LIB_DIR})
target_include_directories(TP4-B PRIVATE ${LIB_DIR})
target_include_directories(TP4-C PRIVATE ${LIB_DIR})
target_include_directories(TP3-A PRIVATE ${LIB_DIR})
target_include_directories(TP3-C PRIVATE ${LIB_DIR})
target_include_directories(TP5 PRIVATE ${LIB_DIR})

# Set the output directories for the library and test executable
set_target_properties(timespec PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(timer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(posix_thread PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(thread PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(mutex PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(semaphore PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(chrono PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set_target_properties(cpu_loop PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

set_target_properties(TP1-ABC PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(TP3-B PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(TP2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(TP4-A PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(TP4-B PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(TP4-C PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(TP3-A PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(TP3-C PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set_target_properties(TP5 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
