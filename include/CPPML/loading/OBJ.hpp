#ifndef OBJ_HPP
#define OBJ_HPP

#include <stdio.h>
#include <memory>
#include <array>
#include <vector>

namespace CPPML { namespace loading {

bool LoadOBJFile(FILE *file, 
const std::unique_ptr<std::vector<std::array<float, 3>>>& vertices, 
const std::unique_ptr<std::vector<std::array<float, 2>>>& texcoords, 
const std::unique_ptr<std::vector<std::array<float, 3>>>& normals);

}}

#endif