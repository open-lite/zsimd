#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcmp.hpp"

#if !defined(ZSTRING_STRCMP_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_STRCMP_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strcmp.hpp"
#include "zsimd/duplicate_foreach.h"


namespace zstring {
    ZSIMD_EXPAND inline
    int strcmp(const char* lhs, const char* rhs, std::size_t str_len) {
        return zstring::memcmp(lhs, rhs, str_len);
    }

    ZSIMD_EXPAND inline
    int strcmp(const char* lhs, const char* rhs) {
        return zstring::strcmp(lhs, rhs, zstring::strlen(lhs));
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif