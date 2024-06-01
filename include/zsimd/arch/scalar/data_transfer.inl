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
    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::loadu(T const* const data) noexcept {
        //With at least 02 optimization, this will compile to a single mov instruction
        return ploadu(data, vector<T>::slots);
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::loada(T const* const data) noexcept {
        return loadu(data);
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::ploadu(T const* const data, std::size_t remaining_len) noexcept {
        vector<T> ret = scalar::all_zeros<T>();
        for(std::size_t i = 0; i < std::min(vector<T>::slots, remaining_len); ++i)
            ret.native()[i] = data[i];
        return ret;
    }



    //TODO
    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::broadcast(T val) noexcept {
        //With at least 02 optimization, this will compile to a single instruction
        vector<T> ret = scalar::all_zeros<T>();
        for(std::size_t i = 0; i < vector<T>::slots; ++i)
            ret.native()[i] = val;
        return ret;
    }
    

    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::all_zeros() noexcept {
        return {{0}};
    }
    
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::all_ones() noexcept {
        //With at least 02 optimization, this will compile to a single mov instruction
        vector<T> ret = scalar::all_zeros<T>();
        for(std::size_t i = 0; i < vector<T>::slots; ++i)
            ret.native()[i] = ~static_cast<T>(0);
        return ret;
    }
}


namespace zsimd {
    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::array<T> scalar::store(scalar::vector<T> v) noexcept {
        //Intended to be a copy.
        //With at least 02 optimization, this will just return
        array<T> ret{};
        for(std::size_t i = 0; i < vector<T>::slots; ++i)
            ret[i] = v.native()[i];
        return ret;
    }
}


namespace zsimd {
    template<typename T> ZSIMD_TARGET_SCALAR_CPP14
    scalar::array<T> scalar::to_array(scalar::vector<T> v) noexcept {
        return store(v);
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::mask<T> scalar::to_mask(scalar::vector<T> v) noexcept {
		mask<T> ret = 0;
		for (std::size_t i = 0; i < vector<T>::slots; ++i)
			ret |= bit_shiftl(bit_shiftr_l(v.native()[i], (vector<T>::slot_size * CHAR_BIT) - 1) & 0b1, vector<T>::slots - i - 1);
		return ret;
    }

    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::bitset<T> scalar::to_bitset(scalar::vector<T> v) noexcept {
        #ifdef __ZSIMD_BIT_CAST
        //with std::bit_cast, this will compile to a single mov instruction
        return std::bit_cast<bitset<T>>(v.natve());
        #else 
        bitset<T> ret{0};
        for(std::size_t i = 0; i < vector<T>::slots; ++i) {
            ret |= v.native()[i];
            ret <<= (vector<T>::slots - i - 1) * vector<T>::slot_size * CHAR_BIT;
        }
        return ret;
        #endif
    }
}


namespace zsimd {
    template<typename To, typename From> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<To> scalar::type_cast(scalar::vector<From> v) noexcept {
        vector<To> ret = scalar::all_zeros<To>();
        for(std::size_t i = 0; i < vector<To>::slots; ++i)
            ret[i] = static_cast<To>(v.native()[i]);
        return ret;
    }

    template<typename To, typename From, enable_if_2<To, From, traits::same_size>> ZSIMD_TARGET_SCALAR_CPP20
    scalar::vector<To> scalar::bit_cast(vector<From> v) noexcept {
        #ifdef __ZSIMD_BIT_CAST
        return {std::bit_cast<typename vector<To>::data_type, typename vector<From>::data_type>(v.native())};
        #else
        vector<To> ret = scalar::all_zeros<To>();
        std::memcpy(ret.native(), v.native(), sizeof(typename vector<To>::data_type));
        #endif
        return ret;
    }
}


namespace zsimd {
    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::mask<T> scalar::right_mask(std::size_t idx) noexcept {
        return static_cast<mask<T>>(~static_cast<mask<T>>(0)) >> idx;
    }
    
    template<typename T> ZSIMD_TARGET_SCALAR
    scalar::mask<T> scalar::left_mask(std::size_t idx) noexcept {
        return static_cast<mask<T>>(~static_cast<mask<T>>(0)) << ((sizeof(mask<T>) * CHAR_BIT) - (idx + 1));
    }
}


namespace zsimd {
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::slot_shiftl(vector<T> v, std::size_t n_slots) noexcept {
        #ifdef __ZSIMD_BIT_CAST
        bitset<T> b = std::bit_cast<bitset<T>>(v.native());
        b <<= n_slots * CHAR_BIT * sizeof(T);
        return std::bit_cast<vector<T>>(b);
        #else
        vector<T> ret{};
        for(std::size_t i = 0; i < vector<T>::slots - n_slots; ++i)
            ret.native()[i] = v.native()[i + n_slots];
        return ret;
        #endif
    }
    
    template<typename T, enable_if<T, traits::integral>> ZSIMD_TARGET_SCALAR_CPP14
    scalar::vector<T> scalar::slot_shiftr(vector<T> v, std::size_t n_slots) noexcept {
        #ifdef __ZSIMD_BIT_CAST
        bitset<T> b = std::bit_cast<bitset<T>>(v.native());
        b >>= n_slots * CHAR_BIT * sizeof(T);
        return std::bit_cast<vector<T>>(b);
        #else
        vector<T> ret{};
        for(std::size_t i = 0; i < vector<T>::slots - n_slots; ++i)
            ret.native()[i + n_slots] = v.native()[i];
        return ret;
        #endif
    }
}