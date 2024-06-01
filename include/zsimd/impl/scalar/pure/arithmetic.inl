#pragma once
#include "zsimd/impl/scalar.hpp"

#include "zsimd/impl/scalar/pure/arithmetic_impl.inl"
#include <algorithm>


namespace zsimd {
    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::add(T a, T b) noexcept {
        return a + b;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::sub(T a, T b) noexcept {
        return a - b; 
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::mul(T a, T b) noexcept {
        return a * b;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::div(T a, T b) noexcept {
        return a / b;
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::mod(T a, T b) noexcept {
        return a % b;
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::mod(T a, T b) noexcept { 
        return a - truncate(a / b) * b;
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    T scalar::rem(T a, T b) noexcept { 
        return a % b;
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::rem(T a, T b) noexcept { 
        return a - half_to_even(a / b) * b;
    }


    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::positive(T val) noexcept { 
        return +val;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::negative(T val) noexcept { 
        return -val;
    }


    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::reciprocal(T val) noexcept { 
        return static_cast<T>(1) / val;
    }


    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::decr(T val) noexcept { 
        return --val;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::incr(T val) noexcept { 
        return ++val;
    }


    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::min(T a, T b) noexcept { 
        return (b < a) ? b : a;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::max(T a, T b) noexcept { 
        return (a < b) ? b : a;
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::integral, traits::unsigned_num>> ZSIMD_TARGET_SCALAR
    T scalar::add_s(T a, T b) noexcept { 
        T ret = a + b; 
        return ret < a ? static_cast<T>(-1) : ret; 
    }
    template<typename T, enable_if<T, traits::integral, traits::signed_num>> ZSIMD_TARGET_SCALAR
    T scalar::add_s(T a, T b) noexcept { 
        #if defined(__ZSIMD_BUILTIN_ADD_S)
        return impl::builtin_sadd_s(a, b);
        #else 
        return impl::scalar_sadd_s(a, b);
        #endif
    }


    template<typename T, enable_if<T, traits::integral, traits::unsigned_num>> ZSIMD_TARGET_SCALAR
    T scalar::sub_s(T a, T b) noexcept {
        T ret = a - b; 
        return ret > a ? static_cast<T>(0) : ret; 
    }

    template<typename T, enable_if<T, traits::integral, traits::signed_num>> ZSIMD_TARGET_SCALAR
    T scalar::sub_s(T a, T b) noexcept {
        #if defined(__ZSIMD_BUILTIN_SUB_S)
        return impl::builtin_ssub_s(a, b);
        #else 
        return impl::scalar_ssub_s(a, b);
        #endif
    }


    template<typename T, enable_if<T, traits::integral, traits::unsigned_num>> ZSIMD_TARGET_SCALAR
    T scalar::mul_s(T a, T b) noexcept {
        T ret = a * b;
        return ret < a ? static_cast<T>(-1) : ret; 
    }

    template<typename T, enable_if<T, traits::integral, traits::signed_num>> ZSIMD_TARGET_SCALAR
    T scalar::mul_s(T a, T b) noexcept {
        #if defined(__ZSIMD_BUILTIN_MUL_S)
        return impl::builtin_smul_s(a, b);
        #else 
        return impl::scalar_smul_s(a, b);
        #endif
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    T scalar::fma(T a, T b, T c) noexcept {
        return a * b + c;
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    T scalar::fms(T a, T b, T c) noexcept {
        return a * b - c;
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    T scalar::fnma(T a, T b, T c) noexcept {
        return -a * b + c;
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    T scalar::fnms(T a, T b, T c) noexcept {
        return -a * b - c;
    }

}


namespace zsimd {
    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::logical_and(T a, T b) noexcept {
        return a && b;
    }

    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::logical_or (T a, T b) noexcept {
        return a || b;
    }


    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    bool scalar::logical_not(T val) noexcept {
        return !val;
    }

}