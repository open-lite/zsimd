#pragma once
#include "zsimd/arch/scalar.hpp"


namespace zsimd {
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::bit_shiftl(scalar::vector<T> v, int shift) noexcept {
        return scalar::per_slot<T>(scalar::bit_shiftl, v, shift);
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::bit_shiftr(scalar::vector<T> v, int shift) noexcept {
        return scalar::per_slot<T>(scalar::bit_shiftr, v, shift);
    }


    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::bit_shiftr_a(scalar::vector<T> v, int shift) noexcept {
        return scalar::per_slot<T>(scalar::bit_shiftr_a, v, shift);
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::bit_shiftr_l(scalar::vector<T> v, int shift) noexcept {
        return scalar::per_slot<T>(scalar::bit_shiftr_l, v, shift);
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::bitwise_not(scalar::vector<T> v) noexcept {
        //With at least 02 optimization, this will compile to just 2 instructions (mov + not)
        return scalar::per_slot<T>(scalar::bitwise_not, v);
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::bitwise_and(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        //With at least 02 optimization, this will compile to just 2 instructions (mov + and)
        return scalar::per_slot<T>(scalar::bitwise_and, a, b);
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::bitwise_or (scalar::vector<T> a, scalar::vector<T> b) noexcept {
        //With at least 02 optimization, this will compile to just 2 instructions (mov + or)
        return scalar::per_slot<T>(scalar::bitwise_or, a, b);
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::bitwise_xor(scalar::vector<T> a, scalar::vector<T> b) noexcept {
        //With at least 02 optimization, this will compile to just 2 instructions (mov + xor)
        return scalar::per_slot<T>(scalar::bitwise_xor, a, b);
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::is_ones(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T, bool>(scalar::is_ones, v);
    }
        
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::is_zeros(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T, bool>(scalar::is_zeros, v);
    }


    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    bool scalar::is_all_ones(scalar::vector<T> v) noexcept {
        //with std::bit_cast, this will compile to just 2 instructions
        return scalar::is_ones(scalar::to_bitset(v).to_ullong());
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    bool scalar::is_all_zeros(scalar::vector<T> v) noexcept {
        //with std::bit_cast, this will compile to just 2 instructions
        return scalar::is_zeros(scalar::to_bitset(v).to_ullong());
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::rotr(scalar::vector<T> v, int shift) noexcept {
        return scalar::per_slot<T>(scalar::rotr, v, shift);
    }
    
    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::rotl(scalar::vector<T> v, int shift) noexcept {
        return scalar::per_slot<T>(scalar::rotl, v, shift);
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::countl_zero(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T, std::uint8_t>(scalar::countl_zero, v);
    }

    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::countr_zero(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T, std::uint8_t>(scalar::countr_zero, v);
    }


    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::countl_one(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T, std::uint8_t>(scalar::countl_one, v);
    }

    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::countr_one(scalar::vector<T> v) noexcept {
        return scalar::per_slot<T, std::uint8_t>(scalar::countr_one, v);
    }


    template<typename T, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::popcount(scalar::vector<T> v) noexcept{
        return scalar::per_slot<T, std::uint8_t>(scalar::popcount, v);
    }
}