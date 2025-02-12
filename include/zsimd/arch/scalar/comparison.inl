#pragma once
#include "zsimd/arch/scalar.hpp"

#include "zsimd/attrib/align.h"


//TODO: Currently doesn't work with floats
namespace zsimd {
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::eq(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>([](T x, T y){ return scalar::eq (x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::neq(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>([](T x, T y){ return scalar::neq(x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::gt(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>([](T x, T y){ return scalar::gt (x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::lt(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>([](T x, T y){ return scalar::lt (x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::geq(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>([](T x, T y){ return scalar::geq(x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::leq(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>([](T x, T y){ return scalar::leq(x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }
}


namespace zsimd {
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::is_even(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, bool>(scalar::is_even, v);
    }
    
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::is_odd(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, bool>(scalar::is_odd, v);
    }
}