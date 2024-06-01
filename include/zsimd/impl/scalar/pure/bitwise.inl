#pragma once
#include "zsimd/impl/scalar.hpp"

#include <cmath>
#include <type_traits>
#include "zsimd/impl/scalar/pure/bitwise_impl.inl"

#if __cpp_lib_bitops >= 201907L
#define __ZSIMD_BITOPS 1
#include <bit>
#endif


namespace zsimd {
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::bit_shiftl(T val, int shift) noexcept {
        //Right shift on signed negative numbers is undefined behavior until C++20, so we can't just use << by itself.
        //We treat it as unsigned and return the left shift of that
        return static_cast<typename std::make_unsigned<T>::type>(val) << shift;
    }

    template<typename T, enable_if<T, traits::integral, traits::unsigned_num>> ZSIMD_TARGET_SCALAR
    T scalar::bit_shiftr(T val, int shift) noexcept {
        return scalar::bit_shiftr_l(val, shift);
    }

    template<typename T, enable_if<T, traits::integral, traits::signed_num>> ZSIMD_TARGET_SCALAR
    T scalar::bit_shiftr(T val, int shift) noexcept {
        return scalar::bit_shiftr_a(val, shift);
    }


    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::bit_shiftr_a(T val, int shift) noexcept {
        //Right shift on signed negative numbers is implementation-defined until C++20, so we can't just use >> by itself.
        //For unsigned or positive signed numbers, it's just a logical shift right
        //For negative signed numbers, invert the bits (to invert the sign), do the logical shift, then invert the bits back again
        return val >= 0 ? bit_shiftr_l(val, shift) : ~bit_shiftr_l(~val, shift);
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::bit_shiftr_l(T val, int shift) noexcept {
        return static_cast<typename std::make_unsigned<T>::type>(val) >> shift;
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::bitwise_not(T val) noexcept {
        return ~val;
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::bitwise_and(T a, T b) noexcept {
        return a & b;
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::bitwise_or (T a, T b) noexcept {
        return a | b;
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::bitwise_xor(T a, T b) noexcept {
        return a ^ b;
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    bool scalar::is_ones (T val) noexcept {
        return val == static_cast<T>(~static_cast<T>(0));
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    bool scalar::is_zeros(T val) noexcept {
        return val == static_cast<T>(0);
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::rotr(T val, int shift) noexcept {
        #if defined(__ZSIMD_BITOPS)
        return std::rotr(val, shift);
        #else
        shift %= std::numeric_limits<T>::digits;
        if(shift > 0) return (val >> shift) | (val << (std::numeric_limits<T>::digits - shift));
        if(shift == 0) return val;
        return rotl(val, -shift);
        #endif
        
    }

    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::rotl(T val, int shift) noexcept {
        #if defined(__ZSIMD_BITOPS)
        return std::rotl(val, shift);
        #else
        shift %= std::numeric_limits<T>::digits;
        if(shift > 0) return (val << shift) | (val >> (std::numeric_limits<T>::digits - shift));
        if(shift == 0) return val;
        return rotr(val, -shift);
        #endif
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    std::uint8_t scalar::countl_zero(T val) noexcept {
        #if   defined(__ZSIMD_BITOPS)
        return std::countl_zero(val);
        #elif defined(__ZSIMD_BUILTIN_LZCNT)
        return impl::builtin_lzcnt(val);
        #else 
        return impl::scalar_lzcnt(val);
        #endif
    }

    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    std::uint8_t scalar::countr_zero(T val) noexcept {
        #if   defined(__ZSIMD_BITOPS)
        return std::countr_zero(val);
        #elif defined(__ZSIMD_BUILTIN_TZCNT)
        return impl::builtin_tzcnt(val);
        #else 
        return impl::scalar_tzcnt(val);
        #endif
    }


    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    std::uint8_t scalar::countl_one(T val) noexcept {
        #if   defined(__ZSIMD_BITOPS)
        return std::countl_one(val);
        #elif defined(__ZSIMD_BUILTIN_LZCNT)
        return impl::builtin_lzcnt(static_cast<T>(~val));
        #else 
        return impl::scalar_lzcnt(static_cast<T>(~val));
        #endif
    }

    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    std::uint8_t scalar::countr_one(T val) noexcept {
        #if   defined(__ZSIMD_BITOPS)
        return std::countr_one(val);
        #elif defined(__ZSIMD_BUILTIN_TZCNT)
        return impl::builtin_tzcnt(static_cast<T>(~val));
        #else 
        return impl::scalar_tzcnt(static_cast<T>(~val));
        #endif
    }


    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    std::uint8_t scalar::popcount(T val) noexcept {
        #if   defined(__ZSIMD_BITOPS)
        return std::popcount(val);
        #elif defined(__ZSIMD_BUILTIN_POPCNT)
        return impl::builtin_popcnt(val);
        #else 
        return impl::scalar_popcnt(val);
        #endif
    }

}