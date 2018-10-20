cmake_minimum_required(VERSION 3.12)
project(half_precision)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(Float16 SHARED src/float16.cpp include/float16.hpp)
