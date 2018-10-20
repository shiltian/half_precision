#include "float16.hpp"
#include <iostream>

uint16_t float2half(const float& val) {
    const uint32_t bits = *reinterpret_cast<const uint32_t*>(&val);
    
    uint16_t ret = 0;
    
    // Extract the sign from the float value
    const uint16_t sign = (bits & 0x80000000) >> 16;
    ret |= sign;
    
    // Extract the exponent from the float value
    uint16_t exp16 = 0;
    const uint8_t exp32 = (bits & 0x7f800000) >> 23;
    const int8_t exp32_diff = exp32 - 127;
    if (exp32 == 0xff || exp32_diff > 15) {
        exp16 = 0x1f;
    } else if (exp32 == 0 || exp32_diff < -14) {
        exp16 = 0;
    } else {
        exp16 = exp32_diff + 15;
    }
    ret |= exp16 << 10;
    
    // Extract the fraction from the float value
    const uint16_t frac = (bits & 0x7fffff) >> 13;
    ret |= frac;
    
    return ret;
}

float half2float(const uint16_t& val) {
    uint32_t bits = 0;
    
    // Extract the sign from the bits
    const uint32_t sign = static_cast<uint32_t>(val & 0x8000) << 16;
    bits |= sign;
    
    // Extract the exponent from the bits
    const uint8_t exp16 = (val & 0x7c00) >> 10;
    uint32_t exp32 = 0;
    if (exp16 == 0xff) {
        exp32 = 0x7f800000;
    } else if (exp16 == 0) {
        exp32 = 0;
    } else {
        exp32 = static_cast<uint32_t>(exp16) + 112;
    }
    bits |= (exp32 << 23);
    
    // Extract the fraction from the bits
    const uint32_t frac = static_cast<uint32_t>(val & 0x3ff) << 13;
    bits |= frac;
    
    return *reinterpret_cast<float*>(&bits);
}

std::ostream& operator<<(std::ostream& os, const half& val) {
    os << static_cast<float>(val);
    return os;
}

std::istream& operator>>(std::istream& is, half& val_h) {
    float val_f = 0.0f;
    is >> val_f;
    val_h = val_f;
    return is;
}

half::half(const float& rhs) : buf(float2half(rhs)) {}

half::operator float() const {
    return half2float(buf);
}

half& half::operator=(const float& rhs) {
    buf = float2half(rhs);
    return *this;
}

// Operator +, -, *, /
half operator+(half lhs, const half& rhs) {
    lhs += rhs;
    return lhs;
}

half operator-(half lhs, const half& rhs) {
    lhs -= rhs;
    return lhs;
}

half operator*(half lhs, const half& rhs) {
    lhs *= rhs;
    return lhs;
}

half operator/(half lhs, const half& rhs) {
    lhs /= rhs;
    return lhs;
}

// Operator <, >, <=, >=
bool operator<(const half& lhs, const half& rhs) {
    return static_cast<float>(lhs) < static_cast<float>(rhs);
}

bool operator>(const half& lhs, const half& rhs) {
    return rhs < lhs;
}

bool operator<=(const half& lhs, const half& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const half& lhs, const half& rhs) {
    return !(lhs < rhs);
}

// Operator ==, !=
bool operator==(const half& lhs, const half& rhs) {
    return static_cast<float>(lhs) == static_cast<float>(rhs);
}

bool operator!=(const half& lhs, const half& rhs) {
    return !(lhs == rhs);
}
