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
    ZSIMD_EXPAND inline
    int strcmp(const char* lhs, const char* rhs, std::size_t str_len) {
        return zstring::memcmp(lhs, rhs, str_len);
    }

    ZSIMD_EXPAND inline
    int strcmp(const char* lhs, const char* rhs) {
        return zstring::strcmp(lhs, rhs, zstring::strlen(lhs));
    }
}

#endif