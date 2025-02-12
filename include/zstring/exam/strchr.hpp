#ifndef ZSTRING_STRCHR_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memchr.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strchr.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRCHR_H
#endif
#include "zstring/fn_traits.hpp"




namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    const char* strchr(const char* str, int ch, std::size_t str_len) noexcept {
        return static_cast<narrow_type const*>(zstring::memchr(str, ch, str_len));
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    const char* strchr(const char* str, int ch) noexcept {
        return zstring::strchr(str, ch, zstring::strlen(str) + 1);
    }


    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strchr(char* str, int ch, std::size_t str_len) noexcept {
        return const_cast<narrow_type*>(zstring::strchr(static_cast<narrow_type const*>(str), ch, str_len));
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strchr(char* str, int ch) noexcept {
        return const_cast<narrow_type*>(zstring::strchr(static_cast<narrow_type const*>(str), ch));
    }
}

namespace zstring { 
    ZSIMD_EXPAND constexpr
    const char* strchr_constexpr(const char* str, int ch, std::size_t str_len) noexcept {
        return static_cast<narrow_type const*>(zstring::memchr_constexpr(str, ch, str_len));
    }

    ZSIMD_EXPAND constexpr
    const char* strchr_constexpr(const char* str, int ch) noexcept {
        return zstring::strchr(str, ch, zstring::strlen(str) + 1);
    }


    ZSIMD_EXPAND constexpr
    char* strchr_constexpr(char* str, int ch, std::size_t str_len) noexcept {
        return const_cast<narrow_type*>(zstring::strchr_constexpr(static_cast<narrow_type const*>(str), ch, str_len));
    }

    ZSIMD_EXPAND constexpr
    char* strchr_constexpr(char* str, int ch) noexcept {
        return const_cast<narrow_type*>(zstring::strchr_constexpr(static_cast<narrow_type const*>(str), ch));
    }
}

#endif