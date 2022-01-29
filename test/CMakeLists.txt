add_executable(Test test.cpp)
target_link_libraries(Test PRIVATE CPPModelLibrary)
target_include_directories(Test PRIVATE ../include/ ../spdlog-1.9.2/include/)
