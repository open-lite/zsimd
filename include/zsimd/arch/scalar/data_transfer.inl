#pragma once
#include "zsimd/arch/scalar.hpp"

#include <climits>

#if __cpp_lib_bit_cast >= 201806L
#define __ZSIMD_BIT_CAST 1
#include <bit>
#else
#include <cstring>
#endif


namespace zsimd {
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::loadu(T const* const data) noexcept {
        //With at least 02 optimization, this will compile to a single mov instruction
        return ploadu(data, basic_vector<T, B>::slots);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::loada(T const* const data) noexcept {
        return loadu(data);
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::ploadu(T const* const data, std::size_t remaining_len) noexcept {
        basic_vector<T, B> ret = scalar::all_zeros<T, B>();
        for(std::size_t i = 0; i < std::min(basic_vector<T, B>::slots, remaining_len); ++i)
            ret.data()[i] = data[i];
        return ret;
    }



    //TODO
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::broadcast(T val) noexcept {
        //With at least 02 optimization, this will compile to a single instruction
        basic_vector<T, B> ret = scalar::all_zeros<T, B>();
        for(std::size_t i = 0; i < basic_vector<T, B>::slots; ++i)
            ret.data()[i] = val;
        return ret;
    }
    

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::all_zeros() noexcept {
        return {{0}};
    }
    
    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::all_ones() noexcept {
        //With at least 02 optimization, this will compile to a single mov instruction
        basic_vector<T, B> ret = scalar::all_zeros<T, B>();
        for(std::size_t i = 0; i < basic_vector<T, B>::slots; ++i)
            ret.data()[i] = ~static_cast<T>(0);
        return ret;
    }
}


namespace zsimd {
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    T* const scalar::storeu(T* const dest, basic_vector<T, B> v) noexcept {
        //Intended to be a copy.
        //With at least 02 optimization, this will compile to just two mov instructions
        for(std::size_t i = 0; i < basic_vector<T, B>::slots; ++i)
            dest[i] = v.data()[i];
        return dest;
    }

    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    T* const scalar::storea(T* const dest, basic_vector<T, B> v) noexcept {
        return storeu(dest, v);
    }
}


namespace zsimd {
    template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_array<T, B> scalar::to_array(scalar::basic_vector<T, B> v) noexcept {
        //With at least 02 optimization, this will just return
        scalar::basic_array<T, B> ret;
        storea(ret.data(), v);
        return ret;
    }

    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_mask<T, B> scalar::to_mask(scalar::basic_vector<T, B> v) noexcept {
		basic_mask<T, B> ret = 0;
		for (std::size_t i = 0; i < basic_vector<T, B>::slots; ++i)
			ret |= bit_shiftl(bit_shiftr_l(v.data()[i], (basic_vector<T, B>::slot_size * CHAR_BIT) - 1) & 0b1, basic_vector<T, B>::slots - i - 1);
		return ret;
    }

    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_bitset<T, B> scalar::to_bitset(scalar::basic_vector<T, B> v) noexcept {
        #ifdef __ZSIMD_BIT_CAST
        //with std::bit_cast, this will compile to a single mov instruction
        return std::bit_cast<basic_bitset<T, B>>(v.data());
        #else 
        basic_bitset<T, B> ret{0};
        for(std::size_t i = 0; i < basic_vector<T, B>::slots; ++i) {
            ret |= v.data()[i];
            ret <<= (basic_vector<T, B>::slots - i - 1) * basic_vector<T, B>::slot_size * CHAR_BIT;
        }
        return ret;
        #endif
    }
}


namespace zsimd {
    template<typename To, typename From, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<To, B> scalar::type_cast(scalar::basic_vector<From, B> v) noexcept {
        basic_vector<To, B> ret = scalar::all_zeros<To, B>();
        for(std::size_t i = 0; i < basic_vector<To, B>::slots; ++i)
            ret[i] = static_cast<To>(v.data()[i]);
        return ret;
    }

    template<typename To, typename From, std::size_t B, enable_if_2<To, From, traits::same_size>> ZSIMD_TARGET_SCALAR_CPP20
    scalar::basic_vector<To, B> scalar::bit_cast(basic_vector<From, B> v) noexcept {
        #ifdef __ZSIMD_BIT_CAST
        return {std::bit_cast<typename basic_vector<To, B>::data_type, typename basic_vector<From, B>::data_type>(v.data())};
        #else
        basic_vector<To, B> ret = scalar::all_zeros<To, B>();
        std::memcpy(ret.data(), v.data(), sizeof(typename basic_vector<To, B>::data_type));
        return ret;
        #endif
    }
}


namespace zsimd {
    template<bool Inclusive, typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_mask<T, B> scalar::right_mask(std::size_t idx) noexcept {
        return static_cast<basic_mask<T, B>>(~static_cast<basic_mask<T, B>>(0)) >> (idx + !Inclusive);
    }
    
    template<bool Inclusive, typename T, std::size_t B> ZSIMD_TARGET_SCALAR
    scalar::basic_mask<T, B> scalar::left_mask(std::size_t idx) noexcept {
        constexpr std::size_t bits = sizeof(basic_mask<T, B>) * CHAR_BIT;
        return static_cast<basic_mask<T, B>>(~static_cast<basic_mask<T, B>>(0)) << (bits - scalar::min(idx + Inclusive, bits));
    }
}


namespace zsimd {
    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::slot_shiftl(basic_vector<T, B> v, std::size_t n_slots) noexcept {
        #ifdef __ZSIMD_BIT_CAST
        basic_bitset<T, B> b = std::bit_cast<basic_bitset<T, B>>(v.data());
        b <<= n_slots * CHAR_BIT * sizeof(T);
        return std::bit_cast<basic_vector<T, B>>(b);
        #else
        basic_vector<T, B> ret{};
        for(std::size_t i = 0; i < basic_vector<T, B>::slots - n_slots; ++i)
            ret.data()[i] = v.data()[i + n_slots];
        return ret;
        #endif
    }
    
    template<typename T, std::size_t B, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::slot_shiftr(basic_vector<T, B> v, std::size_t n_slots) noexcept {
        #ifdef __ZSIMD_BIT_CAST
        basic_bitset<T, B> b = std::bit_cast<basic_bitset<T, B>>(v.data());
        b >>= n_slots * CHAR_BIT * sizeof(T);
        return std::bit_cast<basic_vector<T, B>>(b);
        #else
        basic_vector<T, B> ret{};
        for(std::size_t i = 0; i < basic_vector<T, B>::slots - n_slots; ++i)
            ret.data()[i + n_slots] = v.data()[i];
        return ret;
        #endif
    }
}