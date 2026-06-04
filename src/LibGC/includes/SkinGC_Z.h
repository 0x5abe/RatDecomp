#ifndef _SKINGC_Z_H_
#define _SKINGC_Z_H_
#include "Types_Z.h"

// GQR2/GQR4 = S16 scale 12 for paired-single quantized loads/stores. (signed 4.12 fixed-point format)
// GQR3      = S8 scale 6 for paired-single quantized loads/stores. (signed 2.6 fixed-point format)
static inline void SetupSkinnedVertexQuantization() {
#ifdef __MWERKS__
    register U32 arg_lo;
    register U32 arg_hi;

    // clang-format off
    asm {
            lis     arg_lo, 0x0C07
            addi    arg_hi, arg_lo, 0x0C07
            mtspr   GQR2, arg_hi
            lis     arg_lo, 0x0606
            addi    arg_lo, arg_lo, 0x0606
            mtspr   GQR3, arg_lo
            mtspr   GQR4, arg_hi
    }
#endif
}

#endif // _SKINGC_Z_H_
