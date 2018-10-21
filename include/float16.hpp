#ifndef HALF_PRECISION_LIBRARY_H
#define HALF_PRECISION_LIBRARY_H

#pragma once

#include <cstdint>
#include <functional>

struct float16 {
    float16() = default;
    
    float16(const float16&) = default;
    
    float16(float16&&) = default;
    
    float16(const float& rhs);
    
    float16& operator=(const float& rhs);
    
    // Operator +=, -=, *=, /=
#define BINARY_ARITHMETIC_OPERATOR(OP)                                         \
    float16& operator OP##=(const float16& rhs) {                              \
        *this = operator float() OP static_cast<float>(rhs);                   \
        return *this;                                                          \
    }
    
    BINARY_ARITHMETIC_OPERATOR(+)
    
    BINARY_ARITHMETIC_OPERATOR(-)
    
    BINARY_ARITHMETIC_OPERATOR(*)
    
    BINARY_ARITHMETIC_OPERATOR(/)

#undef BINARY_ARITHMETIC_OPERATOR
    
    // Operator ++, --
    float16& operator++() {
        *this += 1;
        return *this;
    }
    
    float16 operator++(int) {
        float16 ret(*this);
        operator++();
        return ret;
    }
    
    float16& operator--() {
        *this -= 1;
        return *this;
    }
    
    float16 operator--(int) {
        float16 ret(*this);
        operator--();
        return ret;
    }
    
    // Operator float
    operator float() const;
    
    template<typename Key> friend
    struct std::hash;

private:
    uint16_t buf;
};

namespace std {
    
    template<>
    struct hash<float16> {
        std::size_t operator()(const float16& key) const {
            return hash<uint16_t>()(key.buf);
        }
    };
    
}

#endif
