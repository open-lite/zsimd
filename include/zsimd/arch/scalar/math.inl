#pragma once
#include "zsimd/arch/scalar.hpp"


namespace zsimd {
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14
    scalar::basic_vector<T, B> scalar::abs(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::abs, v);    
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::expe (scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::expe, v);        
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::exp2 (scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::exp2, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::exp10(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::exp10, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::expem1(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::expem1, v);    
    }


    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::ln(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::ln, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::log2(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::log2, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::log10(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::log10, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::ln1p(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::ln1p, v);    
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::pow(scalar::basic_vector<T, B> base, scalar::basic_vector<T, B> exp) noexcept {
        return scalar::per_slot<T, B>(scalar::pow, base, exp);    
    }

    
    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::rsqrt(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::rsqrt, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::sqrt(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::sqrt, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::cbrt(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::cbrt, v);    
    }


    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::hypot(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::hypot, a, b);    
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::sin(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::sin, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::cos(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::cos, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::tan(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::tan, v);    
    }


    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::arcsin(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::arcsin, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::arccos(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::arccos, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::arctan(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::arctan, v);    
    }


    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::sinh(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::sinh, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::cosh(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::cosh, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::tanh(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::tanh, v);    
    }


    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::arcsinh(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::arcsinh, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::arccosh(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::arccosh, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::arctanh(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::arctanh, v);    
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::half_to_even(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::half_to_even, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::half_to_inf(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::half_to_inf, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::floor(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::floor, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::ceil(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::ceil, v);    
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR_MATH
    scalar::basic_vector<T, B> scalar::truncate(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::truncate, v);    
    }

}