/*
 * NOTE: main.cpp is how I will test the library as I develop it
 * TODO: 
 * Read up on: parsing, lexer/lexing, regex
 * Read up on multithreaded reading and writing in CPP
 * Look into way to test performance of reading and writing with different methods (something that can track time of function or program execution)
 */

#include <iostream>
#include "CPPML/logging/logging.hpp"

using namespace CPPML;
using namespace logging;

int main()
{
    std::cout << "Hello, World" << std::endl;

    Log::Init();
    CPPML_INFO("Started CPPML");

    return 0;
}