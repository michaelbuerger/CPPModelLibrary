/* Remember! Test has to be either empty or error-less before committing. Even when transferring between computers. */

#include <iostream>
#include <stdio.h>
#include <memory>
#include <array>

#include "CPPML/logging/logging.hpp"
#include "CPPML/loading/loading.hpp"
#include "CPPML/loading/OBJ.hpp"

using namespace CPPML;

int main() {
    CPPML::Log::Init(true); // true turns debug log on, false turns debug log off
    // CPPML::Log::Init(spdlog::level::warn); // alternatively, the logger can be set to only display a certain level or above

    FILE* model = OpenFile("test/models/triangle.obj");

    std::unique_ptr<float[]> vertices;
    std::unique_ptr<float[]> texcoords;
    std::unique_ptr<float[]> normals;
    uint vertexCount;

    bool success = LoadOBJFile(model, vertices, texcoords, normals, vertexCount);

    for(size_t i=0;i<vertexCount * 3;i++) {
       CPPML_INFO("v {}", vertices[i]);
    }

    for(size_t i=0;i<vertexCount * 2;i++) {
       CPPML_INFO("vt {}", texcoords[i]);
    }

    for(size_t i=0;i<vertexCount * 3;i++) {
       CPPML_INFO("vn {}", normals[i]);
    }

    return 0;
}
