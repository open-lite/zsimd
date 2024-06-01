#pragma once
#include "zsimd/impl/scalar.hpp"


namespace zsimd {
    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::abs(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::abs, v);    
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::expe (scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::expe, v);        
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::exp2 (scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::exp2, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::exp10(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::exp10, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::expem1(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::expem1, v);    
    }


    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::ln(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::ln, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::log2(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::log2, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::log10(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::log10, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::ln1p(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::ln1p, v);    
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::pow(scalar::vector<T> base, scalar::vector<T> exp) noexcept {
        return scalar::per_slot<T>(scalar::pow, base, exp);    
    }

    
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::rsqrt(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::rsqrt, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::sqrt(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::sqrt, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::cbrt(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::cbrt, v);    
    }


    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::hypot(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::hypot, a, b);    
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::sin(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::sin, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::cos(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::cos, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::tan(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::tan, v);    
    }


    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::arcsin(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::arcsin, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::arccos(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::arccos, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::arctan(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::arctan, v);    
    }


    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::sinh(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::sinh, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::cosh(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::cosh, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::tanh(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::tanh, v);    
    }


    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::arcsinh(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::arcsinh, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::arccosh(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::arccosh, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::arctanh(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::arctanh, v);    
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::half_to_even(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::half_to_even, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::half_to_inf(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::half_to_inf, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::floor(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::floor, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::ceil(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::ceil, v);    
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::vector<T> scalar::truncate(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::truncate, v);    
    }

}