#ifndef USEFUL_HPP
#define USEFUL_HPP

#include <memory>

/* This doesn't work */
bool LoadOBJFile(const char *address, std::unique_ptr<float[]> &ret_data, std::unique_ptr<uint[]> &ret_indices, uint &ret_vertexCount, uint &ret_dataSize, uint &ret_indicesSize);

#endif