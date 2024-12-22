#include "float16.hpp"
#include <iostream>
#include <emmintrin.h>

uint16_t float2half(const float& val) {
#ifndef __F16CINTRIN_H
  const uint32_t bits = *reinterpret_cast<const uint32_t*>(&val);
  const uint16_t sign = (bits & 0x80000000) >> 16;
  const uint32_t frac32 = bits & 0x7fffff;
  const uint8_t exp32 = (bits & 0x7f800000) >> 23;
  const int8_t exp32_diff = exp32 - 127;

  uint16_t exp16 = 0;
  uint16_t frac16 = frac32 >> 13;

  if (__builtin_expect(exp32 == 0xff || exp32_diff > 15, 0)) {
    exp16 = 0x1f;
  } else if (__builtin_expect(exp32 == 0 || exp32_diff < -14, 0)) {
    exp16 = 0;
  } else {
    exp16 = exp32_diff + 15;
  }

  if (__builtin_expect(exp32 == 0xff && frac32 != 0 && frac16 == 0, 0)) {
    frac16 = 0x200;
  } else if (__builtin_expect(exp32 == 0 || (exp16 == 0x1f && exp32 != 0xff), 0)) {
    frac16 = 0;
  } else if (__builtin_expect(exp16 == 0 && exp32 != 0, 0)) {
    frac16 = 0x100 | (frac16 >> 2);
  }

  uint16_t ret = 0;
  ret |= sign;
  ret |= exp16 << 10;
  ret |= frac16;

  return ret;
#else
  return _cvtss_sh(val, 0);
#endif
}

float half2float(const uint16_t& val) {
#ifndef __F16CINTRIN_H
  const uint32_t sign = static_cast<uint32_t>(val & 0x8000) << 16;
  const uint8_t exp16 = (val & 0x7c00) >> 10;
  uint16_t frac16 = val & 0x3ff;

  uint32_t exp32 = 0;
  if (__builtin_expect(exp16 == 0x1f, 0)) {
    exp32 = 0xff;
  } else if (__builtin_expect(exp16 == 0, 0)) {
    exp32 = 0;
  } else {
    exp32 = static_cast<uint32_t>(exp16) + 112;
  }

  if (__builtin_expect(exp16 == 0 && frac16 != 0, 0)) {
    uint8_t OffSet = 0;
    do {
      ++OffSet;
      frac16 <<= 1;
    } while ((frac16 & 0x400) != 0x400);
    frac16 &= 0x3ff;
    exp32 = 113 - OffSet;
  }

  uint32_t frac32 = frac16 << 13;

  uint32_t bits = 0;
  bits |= sign;
  bits |= (exp32 << 23);
  bits |= frac32;

  return *reinterpret_cast<float*>(&bits);
#else
  return _cvtsh_ss(val);
#endif
}
