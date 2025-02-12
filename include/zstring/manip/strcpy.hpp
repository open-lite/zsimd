#ifndef ZSTRING_STRCPY_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcpy.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/manip/strcpy.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRCPY_H
#endif


namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strcpy(char* dest, const char* src, std::size_t len) noexcept {
        return static_cast<char*>(zstring::memcpy(dest, src, len + 1));
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strcpy(char* dest, const char* src) noexcept {
        return zstring::strcpy(dest, src, zstring::strlen(src));
    }


    ZSIMD_EXPAND constexpr
    char* strcpy_constexpr(char* dest, const char* src, std::size_t len) noexcept {
        return static_cast<char*>(zstring::memcpy_constexpr(dest, src, len + 1));
    }

    ZSIMD_EXPAND constexpr
    char* strcpy_constexpr(char* dest, const char* src) noexcept {
        return zstring::strcpy_constexpr(dest, src, zstring::strlen(src));
    }
}

#endif