project(CS-Games-2018-Operating-Systems-Correction)
cmake_minimum_required(VERSION 3.0)


## GTest
include(ExternalProject)

ExternalProject_Add(gtest-target
  GIT_REPOSITORY https://github.com/google/googletest
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/extern
  UPDATE_COMMAND "")

include_directories(${CMAKE_CURRENT_BINARY_DIR}/extern/include)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/extern/lib)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/extern/lib64)

set(GTEST_LIBRARIES gtest gtest_main pthread)

enable_testing()


## Headers
# kiki.h (kernel module ioctls macros)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../kernel_module/src)
# kiki_api.h (user space api)
include_directories(include)


## Subdirs
add_subdirectory(solution_src)
add_subdirectory(test)
