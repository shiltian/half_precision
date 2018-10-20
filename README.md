# Half Precision Type

A library for 16-bit float half-precision type. All the calculation will be
converted to 32-bit float and then downgrade to 16-bit one.

## Requirement
- CMake 3.2+
- A C++ compiler that supports C++11 standard

## Installation:
```Shell
mkdir build && cd build
cmake ..
make
make install
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
half val = 1.0;
// Do what you want
...
```
### Compilation
```Shell
${CXX} -std=c++11 main.cpp -I/PATH/TO/float.hpp -L/PATH/TO/float16.lib -lFloat16
```
