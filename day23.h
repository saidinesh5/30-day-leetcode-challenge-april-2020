#pragma once

/*
Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

Example 1:

Input: [5,7]
Output: 4

Example 2:

Input: [0,1]
Output: 0
*/

#include <immintrin.h>

#ifndef _MSC_VER
#include <stdalign.h>  //MSVC is missing this?
#else
#include <intrin.h>
#pragma intrinsic(_BitScanReverse)  // https://msdn.microsoft.com/en-us/library/fbxyd7zd.aspx suggests this
#endif

// undefined result for mask=0, like BSR
uint32_t bsr_nonzero(uint32_t mask)
{
// on Intel, bsr has a minor advantage for the first step
// for AMD, BSR is slow so you should use 31-LZCNT.

   //return 31 - _lzcnt_u32(mask);
 // Intel's docs say there should be a _bit_scan_reverse(x), maybe try that with ICC

   #ifdef _MSC_VER
     unsigned long tmp;
     _BitScanReverse(&tmp, mask);
     return tmp;
   #else
     return 31 - __builtin_clz(mask);
   #endif
}

class Solution {

public:
    int rangeBitwiseAnd(int m, int n) {
        if (n == 0) {
            return 0;
        }

        int result = 0;

        // sizeof(int) - 1 to ignore the sign bit
        // Find the longest common prefix
        for (int i = bsr_nonzero(n); i >= 0; i--) {
            int bM = (m & (1 << i)),
                bN = (n & (1 << i));

            if (bM == bN) {
                result |= bM;
            }
            else {
                break;
            }
        }

        return result;
    }
};
