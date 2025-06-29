#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define ANTLR4_C3_EXPORT __declspec(dllexport)
#else
  #define ANTLR4_C3_EXPORT
#endif

ANTLR4_C3_EXPORT void antlr4_c3();
ANTLR4_C3_EXPORT void antlr4_c3_print_vector(const std::vector<std::string> &strings);
