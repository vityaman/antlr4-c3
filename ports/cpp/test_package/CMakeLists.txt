cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(antlr4-c3 CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example antlr4-c3::antlr4-c3)
