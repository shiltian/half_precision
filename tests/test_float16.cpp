//
// Created by Shilei Tian on 2018/10/21.
//

#include <assert.h>
#include <float16.hpp>

const float epsion = 1e-3;

void testBasic() {
    float16 val_h_1 = 1.0, val_h_2 = 2.0;
    float val_f_1 = 1.0, val_f_2 = 2.0;

    assert((val_h_1 + val_h_2) - (val_f_1 + val_f_2) < epsion);
    assert((val_h_1 - val_h_2) - (val_f_1 - val_f_2) < epsion);
    assert((val_h_1 * val_h_2) - (val_f_1 * val_f_2) < epsion);
    assert((val_h_1 / val_h_2) - (val_f_1 / val_f_2) < epsion);

    assert((val_h_1 += val_h_2) - (val_f_1 += val_f_2) < epsion);
    assert((val_h_1 -= val_h_2) - (val_f_1 -= val_f_2) < epsion);
    assert((val_h_1 *= val_h_2) - (val_f_1 *= val_f_2) < epsion);
    assert((val_h_1 /= val_h_2) - (val_f_1 /= val_f_2) < epsion);
}

int main() {
    testBasic();
    return 0;
}
