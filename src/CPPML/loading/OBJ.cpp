#include "CPPML/loading/OBJ.hpp"

#include "CPPML/logging/logging.hpp"
#include "CPPML/useful.hpp"

#include <iostream>
#include <memory>
#include <array>
#include <vector>

namespace CPPML {

// TODO: Version of LoadOBJFile that returns unique_ptrs to 1d arrays

/* Must export: Triangles, Vertices, Texcoords, and Normals */
bool LoadOBJFile(FILE *file, 
std::unique_ptr<std::array<float, 3>[]>& ret_vertices, 
std::unique_ptr<std::array<float, 2>[]>& ret_texcoords, 
std::unique_ptr<std::array<float, 3>[]>& ret_normals, uint& vertexCount) {
    auto tempVertices = std::vector<std::array<float, 3>>();
    auto tempTexcoords = std::vector<std::array<float, 2>>();
    auto tempNormals = std::vector<std::array<float, 3>>();

    auto tempIndices = std::vector<std::array<uint, 3>>();

    // Error handling related stuff
    int currentLine = 1;

    if(file == nullptr) { // FILE pointer invalid, file never opened or was closed before loading
        CPPML_ERROR("In method \"LoadOBJFile\". FILE pointer invalid: File never opened or was closed before loading.");
        return false;
    }

    while(!feof(file)) {
        // Per line operations
        char header[128]; 
        /* Note that if the first sequence of non-whitespace charactes in a line (first string) is too long
         * a segfault will occur
         */
        
        if(fscanf(file, "%s", header) == EOF) {
            CPPML_TRACE("In method \"LoadOBJFile\". Reached end-of-file while attempting to read header of line {}", currentLine);
            break;
        }

        if(!strcmp(header, "v")) {
            float x, y, z;
            if(fscanf(file, "%f %f %f\n", &x, &y, &z) == EOF) {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                return false;
            }

            tempVertices.push_back({ x, y, z });
        } else if(!strcmp(header, "vt")) {
            float u, v;
            if(fscanf(file, "%f %f\n", &u, &v) == EOF) {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                return false;
            }

            tempTexcoords.push_back({ u, v });
        } else if(!strcmp(header, "vn")) {
            float x, y, z;
            if(fscanf(file, "%f %f %f\n", &x, &y, &z) == EOF) {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                return false;
            }

            tempNormals.push_back({ x, y, z });
        } else if(!strcmp(header, "f")) {
            uint vi0, ti0, ni0, vi1, ti1, ni1, vi2, ti2, ni2;
            int res = fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u\n", &vi0, &ti0, &ni0, &vi1, &ti1, &ni1, &vi2, &ti2, &ni2);
            if (res == EOF) {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                CPPML_ERROR("Note: An EOF error can be produced if face specifications don't have the right structure, or are missing information (make sure your export settings are correct and include vertices, texture coordinates, and normals)");
                return false;
            }

            tempIndices.push_back({ vi0 - 1, ti0 - 1, ni0 - 1 });
            tempIndices.push_back({ vi1 - 1, ti1 - 1, ni1 - 1 });
            tempIndices.push_back({ vi2 - 1, ti2 - 1, ni2 - 1 });
        } else { // TODO: Implement ifs for all possible headers (including comment), then add error if unknown header is reached
            CPPML_TRACE("In method \"LoadOBJFile\". Line header of line {} was ignored: \"{}\"", currentLine, header);
            if(ScanTillNewline(file) == EOF) { // reads till new-line, effectively skips to next line
                break;
            }
        }
        currentLine++;
    }
    CPPML_TRACE("In method \"LoadOBJFile\". Reached EOF.");

    vertexCount = tempIndices.size();
    ret_vertices = std::make_unique<std::array<float, 3>[]>(vertexCount);
    ret_texcoords = std::make_unique<std::array<float, 2>[]>(vertexCount);
    ret_normals = std::make_unique<std::array<float, 3>[]>(vertexCount);

    for(size_t i=0; i<vertexCount; i++) {
        ret_vertices[i] = tempVertices[tempIndices[i][0]];
        ret_texcoords[i] = tempTexcoords[tempIndices[i][1]];
        ret_normals[i] = tempNormals[tempIndices[i][2]];
    }

    return true;
}

}
