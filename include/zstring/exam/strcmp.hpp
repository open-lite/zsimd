#ifndef ZSTRING_STRCMP_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcmp.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strcmp.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRCMP_H
#endif

namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    int strcmp(const char* lhs, const char* rhs, std::size_t str_len) noexcept {
        return zstring::memcmp(lhs, rhs, str_len);
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    int strcmp(const char* lhs, const char* rhs) noexcept {
        return zstring::strcmp(lhs, rhs, zstring::strlen(lhs));
    }
}

namespace zstring {
    ZSIMD_EXPAND constexpr
    int strcmp_constexpr(const char* lhs, const char* rhs, std::size_t str_len) noexcept {
        return zstring::memcmp_constexpr(lhs, rhs, str_len);
    }

    ZSIMD_EXPAND constexpr
    int strcmp_constexpr(const char* lhs, const char* rhs) noexcept {
        return zstring::strcmp_constexpr(lhs, rhs, zstring::strlen(lhs));
    }
}

#endif