cmake_minimum_required(VERSION 3.26)
project(MiniHomework2)

set(CMAKE_CXX_STANDARD 17)

add_executable(MiniHomework2 main.cpp)

add_library(libMathServiceLib SHARED IMPORTED)
set_target_properties(libMathServiceLib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libMathServiceLib.dll)

