//
// Created by Shilei Tian on 2018/10/21.
//

#include <cassert>
#include <float16.hpp>
#include <unordered_map>
#include <set>
#include <string>

using namespace std;

void testBasic() {
  float16 val_h_1 = 1.0, val_h_2 = 2.0;
  float val_f_1 = 1.0, val_f_2 = 2.0;

  assert((val_h_1 + val_h_2) - (val_f_1 + val_f_2) < HLF_EPSILON);
  assert((val_h_1 - val_h_2) - (val_f_1 - val_f_2) < HLF_EPSILON);
  assert((val_h_1 * val_h_2) - (val_f_1 * val_f_2) < HLF_EPSILON);
  assert((val_h_1 / val_h_2) - (val_f_1 / val_f_2) < HLF_EPSILON);

  assert((val_h_1 += val_h_2) - (val_f_1 += val_f_2) < HLF_EPSILON);
  assert((val_h_1 -= val_h_2) - (val_f_1 -= val_f_2) < HLF_EPSILON);
  assert((val_h_1 *= val_h_2) - (val_f_1 *= val_f_2) < HLF_EPSILON);
  assert((val_h_1 /= val_h_2) - (val_f_1 /= val_f_2) < HLF_EPSILON);
}

void testCompatibility() {
  unordered_map<float16, string> map;
  map[1.1] = "1.1";
  assert(map[1.1] == "1.1");

  set<float16> half_set;
  half_set.insert(1.1);
  assert(half_set.find(1.1) != half_set.end());
}

int main() {
  testBasic();
  testCompatibility();
  return 0;
}
