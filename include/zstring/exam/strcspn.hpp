#ifndef ZSTRING_STRCSPN_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strcspn.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRCSPN_H
#endif

#include <cstring>


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    std::size_t strcspn(const char* dest, const char* src, std::size_t dest_len, std::size_t i) {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<char>;

        char const* needle = src;
        vector haystack = simd::loadu(dest + i);
        vector res = simd::all_zeros<char>();
        for(; *needle; ++needle)
            res |= simd::eq(haystack, simd::broadcast(*needle));
        if(simd::is_all_zeros(res)) return dest_len;
        return i + simd::countl_zero(simd::to_mask(res));
    }
}
}


namespace zstring {
    ZSIMD_EXPAND inline
    std::size_t strcspn(const char* dest, const char* src, std::size_t dest_len) {
        constexpr static std::size_t N = zsimd::ZSIMD_ARCH::vector<char>::data_size;

        if(dest_len < N) return std::strcspn(dest, src); //TODO

        //TODO add support for if count < N but > a smaller vector size


        {
        std::size_t i = 0;
        for(; i + N <= dest_len; i += N){
            std::size_t ret = zstring::impl::strcspn(dest, src, dest_len, i);
            if(ret == dest_len) continue;
            return ret;
        }
        if (i >= dest_len) return dest_len;
        }

        return zstring::impl::strcspn(dest, src, dest_len, dest_len - N);
    }

    ZSIMD_EXPAND inline
    std::size_t strcspn(const char* dest, const char* src) {
        return zstring::strcspn(dest, src, zstring::strlen(dest));
    }
}

#endif