#ifndef ZSTRING_STRNCAT_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcpy.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/manip/strncat.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRNCAT_H
#endif


namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strncat(char* dest, const char* src, std::size_t count, std::size_t dest_len, std::size_t src_len) noexcept {
        return static_cast<char*>(zstring::memcpy(dest + dest_len, src, std::min(src_len + 1, count)));
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strncat(char* dest, const char* src, std::size_t count) noexcept {
        return zstring::strncat(dest, src, count, zstring::strlen(dest), zstring::strlen(src));
    }


    ZSIMD_EXPAND constexpr
    char* strncat_constexpr(char* dest, const char* src, std::size_t count, std::size_t dest_len, std::size_t src_len) noexcept {
        return static_cast<char*>(zstring::memcpy_constexpr(dest + dest_len, src, std::min(src_len + 1, count)));
    }

    ZSIMD_EXPAND constexpr
    char* strncat_constexpr(char* dest, const char* src, std::size_t count) noexcept {
        return zstring::strncat_constexpr(dest, src, count, zstring::strlen(dest), zstring::strlen(src));
    }
}

#endif