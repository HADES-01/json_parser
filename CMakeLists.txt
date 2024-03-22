cmake_minimum_required(VERSION 3.27.1)
set( CMAKE_CXX_COMPILER "g++.exe" )
set( CMAKE_C_COMPILER "gcc.exe" )

project(json VERSION 1.0)

include(CTest)
enable_testing()
add_subdirectory(tests)