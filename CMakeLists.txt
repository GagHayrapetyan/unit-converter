cmake_minimum_required(VERSION 3.22)
project(Example)

set(CMAKE_CXX_STANDARD 17)

add_executable(Example example.cpp)

add_subdirectory(src)
target_include_directories(Example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Example unit_converter)