#pragma once
#include "zsimd/impl/scalar.hpp"


namespace zsimd {
    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::eq (T a, T b) noexcept {
        return a == b;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::neq(T a, T b) noexcept {
        return a != b;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::gt (T a, T b) noexcept {
        return a > b;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::lt (T a, T b) noexcept {
        return a < b;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::geq(T a, T b) noexcept {
        return a >= b;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::leq(T a, T b) noexcept {
        return a <= b;
    }


    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::is_even(T val) noexcept { 
        return !(val & 0b1); 
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::is_odd (T val) noexcept { 
        return val & 0b1;
    }
}
