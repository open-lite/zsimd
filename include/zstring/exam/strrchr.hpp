#ifndef ZSTRING_STRRCHR_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memrchr.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strrchr.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRRCHR_H
#endif
#include "zstring/fn_traits.hpp"


namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    const char* strrchr(const char* str, int ch, std::size_t str_len) noexcept {
        return static_cast<narrow_type const*>(zstring::memrchr(str, ch, str_len));
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    const char* strrchr(const char* str, int ch) noexcept {
        return zstring::strrchr(str, ch, zstring::strlen(str) + 1);
    }


    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strrchr(char* str, int ch, std::size_t str_len) noexcept {
        return const_cast<narrow_type*>(zstring::strrchr(static_cast<narrow_type const*>(str), ch, str_len));
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strrchr(char* str, int ch) noexcept {
        return const_cast<narrow_type*>(zstring::strrchr(static_cast<narrow_type const*>(str), ch));
    }
}

namespace zstring { 
    ZSIMD_EXPAND constexpr
    const char* strrchr_constexpr(const char* str, int ch, std::size_t str_len) noexcept { 
        return static_cast<narrow_type const*>(zstring::memrchr_constexpr(str, ch, str_len));
    }

    ZSIMD_EXPAND constexpr
    const char* strrchr_constexpr(const char* str, int ch) noexcept {
        return zstring::strrchr(str, ch, zstring::strlen(str) + 1);
    }


    ZSIMD_EXPAND constexpr
    char* strrchr_constexpr(char* str, int ch, std::size_t str_len) noexcept {
        return const_cast<narrow_type*>(zstring::strrchr_constexpr(static_cast<narrow_type const*>(str), ch, str_len));
    }

    ZSIMD_EXPAND constexpr
    char* strrchr_constexpr(char* str, int ch) noexcept {
        return const_cast<narrow_type*>(zstring::strrchr_constexpr(static_cast<narrow_type const*>(str), ch));
    }
}

#endif