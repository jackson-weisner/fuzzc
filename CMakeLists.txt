cmake_minimum_required(VERSION 3.10)

# Project name and C standard
project(MyProject C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect source files
set(SOURCES
        src/api.c
        src/distance.c
        src/match.c
)

add_library(fuzzc_static STATIC ${SOURCES})
add_library(fuzzc_shared SHARED ${SOURCES})

set_target_properties(fuzzc_static PROPERTIES OUTPUT_NAME "fuzzc")
set_target_properties(fuzzc_shared PROPERTIES OUTPUT_NAME "fuzzc")

set(TEST_SOURCES
        tests/main.c
        tests/test_distance.c
        tests/test_api.c
)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests PRIVATE fuzzc_static)