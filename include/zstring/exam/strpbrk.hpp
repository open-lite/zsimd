#include "zstring/exam/strlen.hpp"

#if !defined(ZSTRING_STRPBRK_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_STRPBRK_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strpbrk.hpp"
#include "zsimd/duplicate_foreach.h"

#include <cstring>


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    const char* strpbrk(const char* dest, const char* breakset, std::size_t i) {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<char>;

        char const* needle = breakset;
        vector haystack = simd::loadu(dest + i);
        vector res = simd::all_zeros<char>();
        for(; *needle; ++needle)
            res |= simd::eq(haystack, simd::broadcast(*needle));
        if(!simd::is_all_zeros(res)) return dest + i + simd::countl_zero(simd::to_mask(res));
        return nullptr;
    }
}
}

namespace zstring {
    ZSIMD_EXPAND inline
    const char* strpbrk(const char* dest, const char* breakset, std::size_t dest_len) {
        constexpr static std::size_t N = zsimd::ZSIMD_ARCH::vector<char>::data_size;

        if(dest_len < N) return std::strpbrk(dest, breakset); //TODO

        //TODO add support for if count < N but > a smaller vector size

        {
        std::size_t i = 0;
        for(; i + N <= dest_len; i += N){
            const char* ret = zstring::impl::strpbrk(dest, breakset, i);
            if(ret == nullptr) continue;
            return ret;
        }
        if (i >= dest_len) return nullptr;
        }

        return zstring::impl::strpbrk(dest, breakset, dest_len - N);
    }

    ZSIMD_EXPAND inline
    const char* strpbrk(const char* dest, const char* breakset) {
        return zstring::strpbrk(dest, breakset, zstring::strlen(dest));
    }


    ZSIMD_EXPAND inline
    char* strpbrk(char* dest, const char* breakset, std::size_t dest_len) {
        return const_cast<char*>(zstring::strpbrk(static_cast<const char*>(dest), breakset, dest_len));
    }

    ZSIMD_EXPAND inline
    char* strpbrk(char* dest, const char* breakset) {
        return const_cast<char*>(zstring::strpbrk(static_cast<const char*>(dest), breakset));
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif