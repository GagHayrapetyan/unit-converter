cmake_minimum_required(VERSION 3.22)
project(unit_converter)

set(CMAKE_CXX_STANDARD 17)

add_library(unit_converter SHARED
        unit.h unit.cpp
        data.h  data.cpp
        str_extension.cc
        parser.h parser.cpp
        converter.h converter.cpp
        exception.h exception.cpp)
