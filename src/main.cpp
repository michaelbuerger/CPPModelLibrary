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
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <array>
#include <stdio.h>

#include "CPPML/logging/logging.hpp"
#include "CPPML/useful.hpp"
#include "CPPML/loading/loading.hpp"
#include "CPPML/loading/OBJ.hpp"

using namespace CPPML;
using namespace logging;
using namespace loading;

int main()
{
    Log::Init();
    CPPML_TRACE("Started CPPML");

    const char* modelAddress = "resources/models/cube.obj";

    FILE* model = OpenFile(modelAddress);

    std::unique_ptr<std::array<float, 3>[]> vertices;
    std::unique_ptr<std::array<float, 2>[]> texcoords;
    std::unique_ptr<std::array<float, 3>[]> normals; // Create struct for this
    uint vertexCount;

    LoadOBJFile(model, vertices, texcoords, normals, vertexCount);

    fclose(model);

    return 0;
}