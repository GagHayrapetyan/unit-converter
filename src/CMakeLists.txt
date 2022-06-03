cmake_minimum_required(VERSION 3.22)
project(unit_converter)

set(CMAKE_CXX_STANDARD 17)

add_library(unit_converter SHARED unit.h unit.cpp data.h str_extension.cc data.cpp parser.h parser.cpp converter.h converter.cpp exception.h exception.cpp)
