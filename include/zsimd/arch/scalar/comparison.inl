#pragma once
#include "zsimd/arch/scalar.hpp"

#include "zsimd/attrib/align.h"


//TODO: Currently doesn't work with floats
namespace zsimd {
    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::eq(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>([](T x, T y){ return scalar::eq (x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::neq(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>([](T x, T y){ return scalar::neq(x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::gt(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>([](T x, T y){ return scalar::gt (x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::lt(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>([](T x, T y){ return scalar::lt (x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::geq(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>([](T x, T y){ return scalar::geq(x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::leq(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>([](T x, T y){ return scalar::leq(x, y) ? ~static_cast<T>(0) : 0; }, a, b);
    }
}


namespace zsimd {
    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::is_even(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T, bool>(scalar::is_even, v);
    }
    
    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::is_odd(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T, bool>(scalar::is_odd, v);
    }
}