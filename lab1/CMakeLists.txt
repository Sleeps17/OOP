cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${CMAKE_PROJECT_NAME}_lib count.cpp)
add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)
add_executable(${CMAKE_PROJECT_NAME}_test test_count.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)
target_include_directories(${CMAKE_PROJECT_NAME}_test PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME}_test PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)

add_test(NAME BASIC COMMAND tests01)