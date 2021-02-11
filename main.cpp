#include "preprocessor_magic.hpp"

#include <iostream>
#include <string>

void arg_defs_func(MACRO_ARGDEFS(char, const long&, std::string))
{
    std::cout << "char -> " << a1 << std::endl;
    std::cout << "long& -> " << a2 << std::endl;
    std::cout << "std::string -> " << a3 << std::endl;
}

int main(int, char**) {
    std::cout << "Get variadic macro num\n";
    std::cout << MACRO_ARGS_NUM(int, char, long) << std::endl;

    arg_defs_func('I', 123L, "OK");
}
