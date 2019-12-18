cmake_minimum_required(VERSION 3.15)
project(HW3compi)

set(CMAKE_CXX_STANDARD 14)

add_executable(HW3compi main.cpp hw3_output.hpp hw3_output.cpp semantic.h semantic.cpp offsetStack.h tableStack.cpp offsetStack.cpp structs.h tableStack.h)