cmake_minimum_required(VERSION 3.15)
project(antlr4-c3 CXX)




add_library(antlr4-c3 src/antlr4-c3.cpp)
target_include_directories(antlr4-c3 PUBLIC include)



set_target_properties(antlr4-c3 PROPERTIES PUBLIC_HEADER "include/antlr4-c3.h")
install(TARGETS antlr4-c3)
