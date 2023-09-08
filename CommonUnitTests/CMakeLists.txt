# CMakeLists.txt : CMake project for CommonUnitTests, include source and define
# project specific logic here.

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Set the project name
project(CommonUnitTests)

# Include Google Test framework
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Create test executables for LinkedListUnitTest and StaticVectorUnitTest
add_executable(LinkedListUnitTest LinkedListUnitTest.cpp)
add_executable(StaticVectorUnitTest StaticVectorUnitTest.cpp)

# Include directories
target_include_directories(LinkedListUnitTest PRIVATE "${CMAKE_SOURCE_DIR}/Common/include")
target_include_directories(LinkedListUnitTest PRIVATE "${CMAKE_SOURCE_DIR}/CommonUnitTests")

target_include_directories(StaticVectorUnitTest PRIVATE "${CMAKE_SOURCE_DIR}/Common/include")
target_include_directories(StaticVectorUnitTest PRIVATE "${CMAKE_SOURCE_DIR}/CommonUnitTests")

# Set C++ standards
set_target_properties(LinkedListUnitTest PROPERTIES CXX_STANDARD 14)
set_target_properties(LinkedListUnitTest PROPERTIES CXX_STANDARD_REQUIRED ON)

set_target_properties(StaticVectorUnitTest PROPERTIES CXX_STANDARD 14)
set_target_properties(StaticVectorUnitTest PROPERTIES CXX_STANDARD_REQUIRED ON)

# Link Google Test to your test executables
target_link_libraries(LinkedListUnitTest PRIVATE gtest gtest_main)
target_link_libraries(StaticVectorUnitTest PRIVATE gtest gtest_main)

