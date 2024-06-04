#pragma once
#include "zsimd/arch/scalar.hpp"


namespace zsimd {
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::add(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::add, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::sub(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::sub, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::mul(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::mul, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::div(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::div, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::mod(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::mod, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::rem(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::rem, a, b);
    }

    
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::positive(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::positive, v);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::negative(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::negative, v);
    }


    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::reciprocal(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::reciprocal, v);
    }


    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::decr(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::decr, v);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::incr(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, B>(scalar::incr, v);
    }


    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::min(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::min, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::max(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::max, a, b);
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::add_s(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::add_s, a, b);
    }

    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::sub_s(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::sub_s, a, b);
    }

    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::mul_s(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, B>(scalar::mul_s, a, b);
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::fma(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b, scalar::basic_vector<T, B> c) noexcept {
        return scalar::per_slot<T, B>(scalar::fma, a, b, c);
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::fms(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b, scalar::basic_vector<T, B> c) noexcept {
        return scalar::per_slot<T, B>(scalar::fms, a, b, c);
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::fnma(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b, scalar::basic_vector<T, B> c) noexcept {
        return scalar::per_slot<T, B>(scalar::fnma, a, b, c);
    }

    template<typename T, std::size_t B, enable_if<T, traits::floating>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::fnms(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b, scalar::basic_vector<T, B> c) noexcept {
        return scalar::per_slot<T, B>(scalar::fnms, a, b, c);
    }
}


namespace zsimd {
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> logical_and(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, bool>(scalar::logical_and, a, b);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> logical_or (scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        return scalar::per_slot<T, bool>(scalar::logical_or, a, b);
    }

    
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> logical_not(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, bool>(scalar::logical_not, v);
    }

}