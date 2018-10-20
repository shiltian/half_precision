cmake_minimum_required(VERSION 3.12)
project(half_precision)

set(CMAKE_CXX_STANDARD 11)

add_library(Float16 SHARED float16.cpp float16.hpp)
