#ifndef ZSTRING_STRSTR_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcmp.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strstr.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRSTR_H
#endif

#include <cstring>


namespace zstring {
    ZSIMD_EXPAND inline
    const char* strstr(const char* haystack, const char* needle, std::size_t haystack_len, std::size_t needle_len) {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<char>;
        using mask = simd::mask<char>;
        constexpr static std::size_t N = vector::data_size;

        if(haystack_len + needle_len - 1 < N) return std::strstr(haystack, needle); //TODO

        //TODO add support for if count < N but > a smaller vector size


        vector needle_first = simd::broadcast(needle[0]);
        vector needle_last  = simd::broadcast(needle[needle_len - 1]);

        auto strstr_impl = [=, &needle_first, &needle_last](const char* haystack, const char* needle, std::size_t i) -> const char* {
            vector eq_first = simd::eq(simd::loadu(haystack + i), needle_first);
            vector eq_last  = simd::eq(simd::loadu(haystack + i + needle_len - 1), needle_last);
            vector needles  = simd::bitwise_and(eq_first, eq_last);

            if(simd::is_all_zeros(needles)) return nullptr;
            mask needle_mask = simd::to_mask(needles);
            while(needle_mask) {
                std::size_t needle_idx = simd::countl_zero(needle_mask);
                if(zstring::memcmp(haystack + i + needle_idx + 1, needle + 1, needle_len - 2) == 0)
                    return haystack + i + needle_idx;
                needle_mask &= simd::right_mask<char>(needle_idx + 1);
            }
            return nullptr;
        };



        {
        std::size_t i = 0;
        for(; i + N + needle_len - 1 <= haystack_len; i += N){
            const char* ret = strstr_impl(haystack, needle, i);
            if(ret == nullptr) continue;
            return ret;
        }
        if (i + needle_len - 1 >= haystack_len) return nullptr;
        }

        std::size_t inc = haystack_len - N - (needle_len - 1);
        return strstr_impl(haystack, needle, inc);
    }

    ZSIMD_EXPAND inline
    const char* strstr(const char* haystack, const char* needle) {
        return zstring::strstr(haystack, needle, zstring::strlen(haystack), zstring::strlen(needle));
    }


    ZSIMD_EXPAND inline
    char* strstr(char* haystack, const char* needle, std::size_t haystack_len, std::size_t needle_len) {
        return const_cast<char*>(zstring::strstr(static_cast<const char*>(haystack), needle, haystack_len, needle_len));
    }

    ZSIMD_EXPAND inline
    char* strstr(char* haystack, const char* needle) {
        return const_cast<char*>(zstring::strstr(static_cast<const char*>(haystack), needle));
    }
}

#endif