#ifndef HALF_PRECISION_LIBRARY_H
#define HALF_PRECISION_LIBRARY_H

#pragma once

#include <cstdint>

struct half {
    half() = default;
    
    half(const half&) = default;
    
    half(half&&) = default;
    
    half(const float& rhs);
    
    half& operator=(const float& rhs);
    
    // Operator +=, -=, *=, /=
#define BINARY_ARITHMETIC_OPERATOR(OP)                                         \
    half& operator OP##=(const half& rhs) {                                    \
        *this = operator float() OP static_cast<float>(rhs);                   \
        return *this;                                                          \
    }
    
    BINARY_ARITHMETIC_OPERATOR(+)
    BINARY_ARITHMETIC_OPERATOR(-)
    BINARY_ARITHMETIC_OPERATOR(*)
    BINARY_ARITHMETIC_OPERATOR(/)

#undef BINARY_ARITHMETIC_OPERATOR
    
    // Operator ++, --
    half& operator++() {
        *this += 1;
        return *this;
    }
    
    half operator++(int) {
        half ret(*this);
        operator++();
        return ret;
    }
    
    half& operator--() {
        *this -= 1;
        return *this;
    }
    
    half operator--(int) {
        half ret(*this);
        operator--();
        return ret;
    }
    
    // Operator float
    operator float() const;

private:
    uint16_t buf;
};

#endif
