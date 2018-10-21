link_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(test_float16 test_float16.cpp)
target_link_libraries (test_float16 float16)

add_test(float16 test_float16)
