#pragma once
#include "zsimd/arch/scalar.hpp"
#include <limits>

#if defined __has_builtin
#if __has_builtin (__builtin_add_overflow)
    #define __ZSIMD_BUILTIN_ADD_S 1
#endif
#if __has_builtin (__builtin_sub_overflow)
    #define __ZSIMD_BUILTIN_SUB_S 1
#endif
#if __has_builtin (__builtin_mul_overflow)
    #define __ZSIMD_BUILTIN_MUL_S 1
#endif
#endif


/* saturated signed addition and subtraction implementation details */
namespace zsimd {
namespace impl {
    template<typename T> ZSIMD_TARGET_SCALAR 
    T scalar_sadd_s(T a, T b) noexcept {
        constexpr static T min = std::numeric_limits<T>::min();
        constexpr static T max = std::numeric_limits<T>::max();
        return a < 0 ? (b < min - a ? min : a + b) : (b > max - a ? max : a + b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR 
    T scalar_ssub_s(T a, T b) noexcept {
       return scalar_sadd_s(a, -b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR 
    T scalar_smul_s(T a, T b) noexcept {
        constexpr static T min = std::numeric_limits<T>::min();
        constexpr static T max = std::numeric_limits<T>::max();
        return 
            a > max / b ? max :
            a < min / b ? min :
            a * b;
    }
}
}


namespace zsimd {
namespace impl {
    #ifdef __ZSIMD_BUILTIN_ADD_S
    template<typename T> ZSIMD_TARGET_SCALAR 
    T builtin_sadd_s(T a, T b) noexcept {
        T ret;
        return __builtin_add_overflow(a, b, &ret) ? 
            //XOR broadcasted sign of b with 0b011..111 (all 1's except sign) - equivalent to (b < 0) ? min() : max()
            //Using zsimd function for bit shift since right shift of negative unsigned is implementation-defined until C++20
            zsimd::scalar::bit_shiftr_a(b, std::numeric_limits<T>::digits) ^ std::numeric_limits<T>::max() : 
            ret;
    }
    #endif


    #ifdef __ZSIMD_BUILTIN_SUB_S
    template<typename T> ZSIMD_TARGET_SCALAR 
    T builtin_ssub_s(T a, T b) noexcept {
        T ret;
        return __builtin_sub_overflow(a, b, &ret) ?
            //XOR broadcasted sign of b with 0b100..000 (all 0's except sign) - equivalent to (b < 0) ? max() : min()
            //Using zsimd function for bit shift since right shift of negative unsigned is implementation-defined until C++20
            zsimd::scalar::bit_shiftr_a(b, std::numeric_limits<T>::digits) ^ std::numeric_limits<T>::min() : 
            ret;
    }
    #endif


    #ifdef __ZSIMD_BUILTIN_MUL_S    
    template<typename T> ZSIMD_TARGET_SCALAR 
    T builtin_smul_s(T a, T b) noexcept {
        T ret;
        return __builtin_mul_overflow(a, b, &ret) ? 
            //XOR broadcasted sign b with that of a and XOR that with 0b011..111 (all 1's except sign) - equivalent to (sign of b != sign of a) ? min() : max()
            //Using zsimd function for bit shift since right shift of negative unsigned is implementation-defined until C++20
            (zsimd::scalar::bit_shiftr_a(a, std::numeric_limits<T>::digits) ^ zsimd::scalar::bit_shiftr_a(b, std::numeric_limits<T>::digits)) 
            ^ std::numeric_limits<T>::max() : ret;
    }
    #endif
}
}