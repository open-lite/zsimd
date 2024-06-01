#pragma once
#include "zsimd/arch/scalar.hpp"


#if defined __has_builtin
#if __has_builtin (__builtin_ctz)
    #define __ZSIMD_BUILTIN_TZCNT 1
#endif
#if __has_builtin (__builtin_clz)
    #define __ZSIMD_BUILTIN_LZCNT 1
#endif
#if __has_builtin (__builtin_popcount)
    #define __ZSIMD_BUILTIN_POPCNT 1
#endif
#endif


/* popcount, countl_zero, and countr_zero implementation details */
namespace zsimd {
namespace impl {
    template<typename T> ZSIMD_TARGET_SCALAR_CPP14 
    std::size_t scalar_lzcnt(T val) noexcept {
        for (std::size_t i = 0; i < sizeof(T) * 8; ++i) 
		    if(val & (0b1 << ((sizeof(T) * 8) - i - 1))) 
			    return i;
		return sizeof(T) * 8;
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14 
    std::size_t scalar_tzcnt(T val) noexcept {
        for (std::size_t i = 0; i < sizeof(T) * 8; ++i)
		    if(val & (0b1 << i)) 
			    return i;
		return sizeof(T) * 8;
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14 
    std::size_t scalar_popcnt(T val) noexcept {
        std::size_t ret = 0;
        for(std::size_t i = 0; i < sizeof(T) * 8; ++i)
            if(val & (0b1 << i))
                ++ret;
        return ret;
    }
}
}


namespace zsimd {
namespace impl {
    #ifdef __ZSIMD_BUILTIN_LZCNT
    ZSIMD_TARGET_SCALAR_CPP14
    std::size_t builtin_lzcnt(unsigned int x) noexcept {
        return __builtin_clz(x);
    }
    
    ZSIMD_TARGET_SCALAR_CPP14
    std::size_t builtin_lzcnt(unsigned long x) noexcept {
        return __builtin_clzl(x);
    }
    
    ZSIMD_TARGET_SCALAR_CPP14
    std::size_t builtin_lzcnt(unsigned long long x) noexcept {
        return __builtin_clzll(x);
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14 
    std::size_t builtin_lzcnt(T val) noexcept {
        return scalar_lzcnt(val);
    }
    #endif


    #ifdef __ZSIMD_BUILTIN_TZCNT
    ZSIMD_TARGET_SCALAR_CPP14
    std::size_t builtin_tzcnt(unsigned int x) noexcept {
        return __builtin_ctz(x);
    }
    
    ZSIMD_TARGET_SCALAR_CPP14
    std::size_t builtin_tzcnt(unsigned long x) noexcept {
        return __builtin_ctzl(x);
    }
    
    ZSIMD_TARGET_SCALAR_CPP14
    std::size_t builtin_tzcnt(unsigned long long x) noexcept {
        return __builtin_ctzll(x);
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14 
    std::size_t builtin_tzcnt(T val) noexcept {
        return scalar_tzcnt(val);
    }
    #endif


    #ifdef __ZSIMD_BUILTIN_TZCNT    
    ZSIMD_TARGET_SCALAR_CPP14
    std::size_t builtin_popcnt(unsigned int x) noexcept {
        return __builtin_popcount(x);
    }
    
    ZSIMD_TARGET_SCALAR_CPP14
    std::size_t builtin_popcnt(unsigned long x) noexcept {
        return __builtin_popcountl(x);
    }
    
    ZSIMD_TARGET_SCALAR_CPP14
    std::size_t builtin_popcnt(unsigned long long x) noexcept {
        return __builtin_popcountll(x);
    }

    template<typename T> ZSIMD_TARGET_SCALAR_CPP14 
    std::size_t builtin_popcnt(T val) noexcept {
        return scalar_popcnt(val);
    }
    #endif
}
}