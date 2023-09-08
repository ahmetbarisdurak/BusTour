# CMakeLists.txt : CMake project for MyProjectMain, include source and define
# project specific logic here.

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Set the project name
project(BusTourMain)

# Add the MyProjectMain executable
add_executable(BusTourMain "BusTour.cpp")

# Include directories
target_include_directories(BusTourMain PRIVATE "${CMAKE_SOURCE_DIR}/Common/include")
target_include_directories(BusTourMain PRIVATE "${CMAKE_SOURCE_DIR}/CommonUnitTests")

# Set C++ standards
set_target_properties(BusTourMain PROPERTIES CXX_STANDARD 14)
set_target_properties(BusTourMain PROPERTIES CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

target_link_libraries(BusTourMain PRIVATE gtest gtest_main)
