# CMakeList.txt : CMake project for BusTour, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("BusTour")


add_subdirectory ("BusTourMain")
add_subdirectory("Common")
add_subdirectory("CommonUnitTests")




# TODO: Add tests and install targets if needed.
