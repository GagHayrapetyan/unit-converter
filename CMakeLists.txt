cmake_minimum_required(VERSION 3.22)
project(unit_converter)

set(CMAKE_CXX_STANDARD 17)

add_executable(unit_converter main.cpp unit.h unit.cpp data.h)
