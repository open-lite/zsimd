#ifndef ZSTRING_STRNCMP_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcmp.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strncmp.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRNCMP_H
#endif
#include "zstring/fn_traits.hpp"



namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    int strncmp(const char* lhs, const char* rhs, std::size_t count, std::size_t str_len) noexcept {
        return zstring::memcmp(lhs, rhs, std::min(count, str_len));
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    int strncmp(const char* lhs, const char* rhs, std::size_t count) noexcept {
        return zstring::strncmp(lhs, rhs, count, zstring::strlen(lhs));
    }


    ZSIMD_EXPAND constexpr
    int strncmp_constexpr(const char* lhs, const char* rhs, std::size_t count, std::size_t str_len) noexcept {
        return zstring::memcmp(lhs, rhs, std::min(count, str_len));
    }

    ZSIMD_EXPAND constexpr
    int strncmp_constexpr(const char* lhs, const char* rhs, std::size_t count) noexcept {
        return zstring::strncmp(lhs, rhs, count, zstring::strlen(lhs));
    }
}

#endif