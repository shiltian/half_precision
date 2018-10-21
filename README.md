# Half Precision Type

A library for 16-bit float float16-precision type. All the calculation will be
converted to 32-bit float and then downgrade to 16-bit one.

## Requirement
- CMake 3.2+
- A C++ compiler that supports C++11 standard

## Installation & Test:
```Shell
mkdir build && cd build
cmake ..
make
make install
# test if needed
make test
```

## Usage
### Source file
```C++
...
// main.cpp
// Include the header
#include <float16.hpp>
...
// Define a value
float16 val = 1.0;
// Do what you want
...
```
### Compilation
```Shell
${CXX} -std=c++11 main.cpp -I/PATH/TO/float16.hpp -L/PATH/TO/float16.lib -lfloat16
```
