#pragma once
#include "zsimd/impl/scalar.hpp"

#include <cmath>


namespace zsimd {
    template<typename T, enable_if<T, traits::arithmetic>> ZSIMD_TARGET_SCALAR
    T scalar::abs(T val) noexcept {
        return val >= static_cast<T>(0) ? val : -val;
    }
}

/* TODO replace standard library math functions with compile time (without errno) counterparts */
namespace zsimd {
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::expe (T val) noexcept {
        return std::exp(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::exp2 (T val) noexcept {
        return std::exp2(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::exp10(T val) noexcept {
        return std::pow(10, val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::expem1(T val) noexcept {
        return std::expm1(val);
    }


    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::ln(T val) noexcept {
        return std::log(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::log2(T val) noexcept {
        return std::log2(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::log10(T val) noexcept {
        return std::log10(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::ln1p(T val) noexcept {
        return std::log1p(val);
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::pow(T base, T exp) noexcept {
        return std::pow(base, exp);
    }

    
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::rsqrt(T val) noexcept {
        return static_cast<T>(1) / scalar::sqrt(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::sqrt(T val) noexcept {
        return std::sqrt(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::cbrt(T val) noexcept {
        return std::cbrt(val);
    }


    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::hypot(T a, T b) noexcept {
        return std::hypot(a, b);
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::sin(T val) noexcept {
        return std::sin(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::cos(T val) noexcept {
        return std::cos(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::tan(T val) noexcept {
        return std::tan(val);
    }


    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::arcsin(T val) noexcept {
        return std::asin(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::arccos(T val) noexcept {
        return std::acos(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::arctan(T val) noexcept {
        return std::atan(val);
    }


    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::sinh(T val) noexcept {
        return std::sinh(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::cosh(T val) noexcept {
        return std::cosh(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::tanh(T val) noexcept {
        return std::tanh(val);
    }


    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::arcsinh(T val) noexcept {
        return std::asinh(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::arccosh(T val) noexcept {
        return std::acosh(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::arctanh(T val) noexcept {
        return std::atanh(val);
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::half_to_even(T val) noexcept {
        return std::round(val / static_cast<T>(2)) * static_cast<T>(2);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::half_to_inf(T val) noexcept {
        return std::round(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::floor(T val) noexcept {
        return std::floor(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::ceil(T val) noexcept {
        return std::ceil(val);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    T scalar::truncate(T val) noexcept {
        return std::trunc(val);
    }
}
