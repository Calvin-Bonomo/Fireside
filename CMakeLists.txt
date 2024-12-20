cmake_minimum_required(version 3.3...)

project(Fireside 0.7)

set(CMAKE_CXX_STANDARD 14)

set(FIRESIDE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(src)

if (BUILD_TESTS)
  add_subdirectory(tests)
endif()