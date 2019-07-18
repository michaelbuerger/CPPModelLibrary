/*
 * NOTE: main.cpp is how I will test the library as I develop it
 * TODO: 
 * Read up on: parsing, lexer/lexing, regex
 * Read up on multithreaded reading and writing in CPP
 * Look into way to test performance of reading and writing with different methods (something that can track time of function or program execution)
 */

/*
 * Links:
 * https://www.quora.com/Whats-the-difference-between-a-tokenizer-lexer-and-parser
 * https://en.wikipedia.org/wiki/Lexical_analysis
 * https://en.wikipedia.org/wiki/Regular_expression
 * https://www.regexbuddy.com/regex.html
 * http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/#reading-the-file
 * NOTE ^^^^ Use of C's fscanf to read patterns in strings to data structures
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include "CPPML/logging/logging.hpp"
#include "CPPML/useful.hpp"

using namespace CPPML;
using namespace logging;

int main()
{
    std::cout << "Hello, World" << std::endl;

    Log::Init();
    CPPML_INFO("Started CPPML");

    std::unique_ptr<float[]> data;
    std::unique_ptr<uint[]> indices;
    uint vertexCount;
    uint dataBytes;
    uint indicesBytes;

    LoadOBJFile("resources/models/square.obj", data, indices, vertexCount, dataBytes, indicesBytes);

    std::cout << "Data: " << std::endl;
    for(size_t i=0;i<vertexCount;i++)
    {
        std::cout << "[ ";
        for(size_t j=0;j<8;j++)
        {
            std::cout << data[i*j] << ", ";
        }
        std::cout << "]" << std::endl;
    }

    std::cout << std::endl << "Indices: " << std::endl;

    std::cout << "[ ";
    for(size_t i=0;i<vertexCount;i++)
    {
        std::cout << indices[i] << ", ";
    }
    std::cout << "]" << std::endl;

    return 0;
}