cmake_minimum_required(VERSION 3.5)

project(lab6)

set(SOURCES
        src/elf.cpp
        src/NPC.cpp
        src/outlaw.cpp
        src/squirrel.cpp
        main.cpp
)

include_directories(headers)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab6_exe ${SOURCES})
set_target_properties(lab6_exe PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)
