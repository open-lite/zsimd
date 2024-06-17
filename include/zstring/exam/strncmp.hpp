#ifndef ZSTRING_STRNCMP_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcmp.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strncmp.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRNCMP_H
#endif



namespace zstring {
    ZSIMD_EXPAND inline
    int strncmp(const char* lhs, const char* rhs, std::size_t count, std::size_t str_len) {
        return zstring::memcmp(lhs, rhs, std::min(count, str_len));
    }

    ZSIMD_EXPAND inline
    int strncmp(const char* lhs, const char* rhs, std::size_t count) {
        return zstring::strncmp(lhs, rhs, count, zstring::strlen(lhs));
    }
}

#endif