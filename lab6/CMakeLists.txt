cmake_minimum_required(VERSION 3.5)

project(lab6)

set(SOURCES
        src/elf.cpp
        src/NPC.cpp
        src/outlaw.cpp
        src/squirrel.cpp
        main.cpp
)

set(TEST_SOURCES
        test.cpp
        tests/test_npcs.cpp
        tests/test_factory.cpp
        tests/test_factory.cpp
)

include_directories(headers)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab6_exe ${SOURCES})
add_executable(lab6_test ${TEST_SOURCES})

target_include_directories(lab6_test PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(lab6_test PRIVATE gtest gtest_main)

set_target_properties(lab6_exe PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

set_target_properties(lab6_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)