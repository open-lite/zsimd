#pragma once
#include "zsimd/arch/scalar.hpp"


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::bit_shiftl(scalar::basic_vector<T, B> v, int shift) noexcept {
        return scalar::per_slot<T, B>(scalar::bit_shiftl, v, shift);
    }

    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::bit_shiftr(scalar::basic_vector<T, B> v, int shift) noexcept {
        return scalar::per_slot<T, B>(scalar::bit_shiftr, v, shift);
    }


    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::bit_shiftr_a(scalar::basic_vector<T, B> v, int shift) noexcept {
        return scalar::per_slot<T, B>(scalar::bit_shiftr_a, v, shift);
    }

    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::bit_shiftr_l(scalar::basic_vector<T, B> v, int shift) noexcept {
        return scalar::per_slot<T, B>(scalar::bit_shiftr_l, v, shift);
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::bitwise_not(scalar::basic_vector<T, B> v) noexcept {
        //With at least 02 optimization, this will compile to just 2 instructions (mov + not)
        return scalar::per_slot<T, B>(scalar::bitwise_not, v);
    }

    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::bitwise_and(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        //With at least 02 optimization, this will compile to just 2 instructions (mov + and)
        return scalar::per_slot<T, B>(scalar::bitwise_and, a, b);
    }

    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::bitwise_or (scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        //With at least 02 optimization, this will compile to just 2 instructions (mov + or)
        return scalar::per_slot<T, B>(scalar::bitwise_or, a, b);
    }

    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::bitwise_xor(scalar::basic_vector<T, B> a, scalar::basic_vector<T, B> b) noexcept {
        //With at least 02 optimization, this will compile to just 2 instructions (mov + xor)
        return scalar::per_slot<T, B>(scalar::bitwise_xor, a, b);
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::is_ones(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, bool>(scalar::is_ones, v);
    }
        
    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::is_zeros(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, bool>(scalar::is_zeros, v);
    }


    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    bool scalar::is_all_ones(scalar::basic_vector<T, B> v) noexcept {
        for(std::size_t i = 0; i < scalar::basic_vector<T, B>::blocks; ++i)
            if(!scalar::is_ones(v.data()[i]))
                return false;
        return true;
    }

    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    bool scalar::is_all_zeros(scalar::basic_vector<T, B> v) noexcept {
        for(std::size_t i = 0; i < scalar::basic_vector<T, B>::blocks; ++i)
            if(!scalar::is_zeros(v.data()[i]))
                return false;
        return true;
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::rotr(scalar::basic_vector<T, B> v, int shift) noexcept {
        return scalar::per_slot<T, B>(scalar::rotr, v, shift);
    }
    
    template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::rotl(scalar::basic_vector<T, B> v, int shift) noexcept {
        return scalar::per_slot<T, B>(scalar::rotl, v, shift);
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::countl_zero(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, std::uint8_t>(scalar::countl_zero, v);
    }

    template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::countr_zero(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, std::uint8_t>(scalar::countr_zero, v);
    }


    template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::countl_one(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, std::uint8_t>(scalar::countl_one, v);
    }

    template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::countr_one(scalar::basic_vector<T, B> v) noexcept {
        return scalar::per_slot<T, std::uint8_t>(scalar::countr_one, v);
    }


    template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::popcount(scalar::basic_vector<T, B> v) noexcept{
        return scalar::per_slot<T, std::uint8_t>(scalar::popcount, v);
    }
}