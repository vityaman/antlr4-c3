cmake_minimum_required(VERSION 3.7)
project(antlr4-c3-demo)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(FetchContent)

FetchContent_Declare(
    antlr4-c3
    GIT_REPOSITORY https://github.com/mike-lischke/antlr4-c3
    GIT_TAG main
    SOURCE_SUBDIR ports/cpp
)

FetchContent_MakeAvailable(antlr4-c3)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE antlr4-c3)
