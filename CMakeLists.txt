cmake_minimum_required (VERSION 3.5)

project (CPPModelLibrary)
set (CPPModelLibrary_VERSION_MAJOR 0)
set (CPPModelLibrary_VERSION_MINOR 1)
set (CPPModelLibrary_VERSION_PATCH 0)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

set (source_dir "${PROJECT_SOURCE_DIR}/src")
set (header_dir "${PROJECT_SOURCE_DIR}/include")
set (test_dir "${PROJECT_SOURCE_DIR}/test")

file (GLOB_RECURSE source_files "${source_dir}/*.cpp")
file (GLOB_RECURSE header_files "${header_dir}/*.hpp" "${header_dir}/*.h")

set (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

add_subdirectory ("${PROJECT_SOURCE_DIR}/spdlog-1.x/")

add_executable (CPPModelLibrary ${source_files} ${header_files})

target_link_libraries (CPPModelLibrary)
target_include_directories (
	CPPModelLibrary PRIVATE
    include/
	spdlog-1.x/include/
)