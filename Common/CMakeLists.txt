# CMakeList.txt : CMake project for StaticVectorLibrary, include source and define
# project specific logic here.
#

include_directories("include")

# Add source to this project's executable.
add_library (Common STATIC "src/StaticVectorLibrary.cpp" "src/LinkedListLibrary.cpp" "include/LinkedListIterator.h" "include/StaticVectorIterator.h")

set_target_properties(Common PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)


if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Common PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

