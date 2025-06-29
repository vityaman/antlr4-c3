#include "antlr4-c3.h"
#include <vector>
#include <string>

int main() {
    antlr4_c3();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    antlr4_c3_print_vector(vec);
}
