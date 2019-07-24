#include <stdio.h>

namespace CPPML { namespace loading {

FILE* TryOpenFile(const char* address) {
    FILE* file = fopen(address, "r"); // tries to open file at address and creates buffer (heap allocated)

    if(file != nullptr) {
        return file;
    }

    return nullptr;
}

}}