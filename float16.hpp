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
    half& operator+=(const half& rhs) {
        *this = operator float() + static_cast<float>(rhs);
        return *this;
    }
    
    half& operator-=(const half& rhs) {
        *this = operator float() - static_cast<float>(rhs);
        return *this;
    }
    
    half& operator*=(const half& rhs) {
        *this = operator float() * static_cast<float>(rhs);
        return *this;
    }
    
    half& operator/=(const half& rhs) {
        *this = operator float() / static_cast<float>(rhs);
        return *this;
    }
    
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
