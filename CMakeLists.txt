cmake_minimum_required(VERSION 3.2)

project(float16 VERSION 1.0.0 DESCRIPTION "A half-precision float type")

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(float16 SHARED src/float16.cpp include/float16.hpp)

set_target_properties(float16 PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER include/float16.hpp)

include(GNUInstallDirs)
install(TARGETS float16
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

enable_testing()

add_subdirectory(tests)


