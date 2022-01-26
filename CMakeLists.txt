cmake_minimum_required (VERSION 3.5)

project (CPPModelLibrary)
set (CPPModelLibrary_VERSION_MAJOR 0)
set (CPPModelLibrary_VERSION_MINOR 1)
set (CPPModelLibrary_VERSION_PATCH 0)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")

set (source_dir "${PROJECT_SOURCE_DIR}/src")
set (header_dir "${PROJECT_SOURCE_DIR}/include")

file (GLOB_RECURSE source_files "${source_dir}/*.cpp")
file (GLOB_RECURSE header_files "${header_dir}/*.hpp" "${header_dir}/*.h")

add_library (CPPModelLibrary STATIC ${source_files})

target_link_libraries (CPPModelLibrary ${PROJECT_SOURCE_DIR}/spdlog-1.9.2/build/libspdlog.a)
target_include_directories (
    CPPModelLibrary PRIVATE
    include/
    spdlog-1.9.2/include/
)

set (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/test")
add_executable (CPPModelLibrary_test ${source_files} ${PROJECT_SOURCE_DIR}/test/test.cpp)

target_link_libraries (CPPModelLibrary_test ${PROJECT_SOURCE_DIR}/spdlog-1.9.2/build/libspdlog.a)
target_include_directories (
    CPPModelLibrary_test PRIVATE
    include/
    spdlog-1.9.2/include/
)
