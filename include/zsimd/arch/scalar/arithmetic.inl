#pragma once
#include "zsimd/arch/scalar.hpp"


namespace zsimd {
    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::add(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::add, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::sub(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::sub, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::mul(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::mul, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::div(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::div, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::mod(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::mod, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::rem(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::rem, a, b);
    }

    
    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::positive(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::positive, v);
    }

    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::negative(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::negative, v);
    }


    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::reciprocal(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::reciprocal, v);
    }


    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::decr(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::decr, v);
    }

    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::incr(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T>(scalar::incr, v);
    }


    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::min(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::min, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::max(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::max, a, b);
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::add_s(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::add_s, a, b);
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::sub_s(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::sub_s, a, b);
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::mul_s(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T>(scalar::mul_s, a, b);
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::fma(scalar::vector<T> a, scalar::vector<T> b, scalar::vector<T> c) noexcept {
        return scalar::per_slot<T>(scalar::fma, a, b, c);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::fms(scalar::vector<T> a, scalar::vector<T> b, scalar::vector<T> c) noexcept {
        return scalar::per_slot<T>(scalar::fms, a, b, c);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::fnma(scalar::vector<T> a, scalar::vector<T> b, scalar::vector<T> c) noexcept {
        return scalar::per_slot<T>(scalar::fnma, a, b, c);
    }

    template<typename T, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::fnms(scalar::vector<T> a, scalar::vector<T> b, scalar::vector<T> c) noexcept {
        return scalar::per_slot<T>(scalar::fnms, a, b, c);
    }
}


namespace zsimd {
    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> logical_and(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T, bool>(scalar::logical_and, a, b);
    }

    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> logical_or (scalar::vector<T> a, scalar::vector<T> b) noexcept {
        return scalar::per_slot<T, bool>(scalar::logical_or, a, b);
    }

    
    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> logical_not(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T, bool>(scalar::logical_not, v);
    }

}