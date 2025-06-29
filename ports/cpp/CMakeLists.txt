cmake_minimum_required(VERSION 3.15)
project(antlr4-c3 CXX)

find_package(antlr4-runtime REQUIRED)

add_library(${PROJECT_NAME} src/antlr4-c3.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} antlr4_static)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/antlr4-c3.hpp")

install(TARGETS ${PROJECT_NAME})
