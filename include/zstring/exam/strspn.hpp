#ifndef ZSTRING_STRSPN_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strspn.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRSPN_H
#endif

#include <cstring>


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    std::size_t strspn(const char* dest, const char* src, std::size_t dest_len, std::size_t i) {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<char>;

        char const* needle = src;
        vector haystack = simd::loadu(dest + i);
        vector res = simd::all_zeros<char>();
        for(; *needle; ++needle)
            res |= simd::eq(haystack, simd::broadcast(*needle));
        if(simd::is_all_ones(res)) return dest_len;
        return i + simd::countl_one(simd::to_mask(res));
    }
}
}


namespace zstring {
    ZSIMD_EXPAND inline
    std::size_t strspn(const char* dest, const char* src, std::size_t dest_len) {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<char>;
        constexpr static std::size_t N = vector::data_size;

        if(dest_len < N) return std::strspn(dest, src); //TODO

        //TODO add support for if count < N but > a smaller vector size


        {
        std::size_t i = 0;
        for(; i + N <= dest_len; i += N){
            std::size_t ret = zstring::impl::strspn(dest, src, dest_len, i);
            if(ret == dest_len) continue;
            return ret;
        }
        if (i >= dest_len) return dest_len;
        }

        return zstring::impl::strspn(dest, src, dest_len, dest_len - N);
    }

    ZSIMD_EXPAND inline
    std::size_t strspn(const char* dest, const char* src) {
        return zstring::strspn(dest, src, zstring::strlen(dest));
    }
}

#endif