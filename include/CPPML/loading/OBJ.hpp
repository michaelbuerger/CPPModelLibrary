#ifndef OBJ_HPP
#define OBJ_HPP

#include <stdio.h>
#include <memory>
#include <array>
#include <vector>

namespace CPPML {

/* Must export: Triangles, Vertices, Texcoords, and Normals */
bool LoadOBJFile(FILE *file, 
std::unique_ptr<std::array<float, 3>[]>& ret_vertices, 
std::unique_ptr<std::array<float, 2>[]>& ret_texcoords, 
std::unique_ptr<std::array<float, 3>[]>& ret_normals, uint& vertexCount);

}

#endif