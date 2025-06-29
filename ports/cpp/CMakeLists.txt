cmake_minimum_required(VERSION 3.15)
project(antlr4-c3 CXX)

find_package(antlr4-runtime REQUIRED)

add_library(antlr4-c3 src/antlr4-c3.cpp)
target_include_directories(antlr4-c3 PUBLIC include)

target_link_libraries(antlr4-c3 antlr4_static)

set_target_properties(antlr4-c3 PROPERTIES PUBLIC_HEADER "include/antlr4-c3.hpp")
install(TARGETS antlr4-c3)
