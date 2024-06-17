#ifndef ZSTRING_STRCHR_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memchr.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strchr.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRCHR_H
#endif




namespace zstring {
    ZSIMD_EXPAND inline
    const char* strchr(const char* str, int ch, std::size_t str_len) {
        return static_cast<const char*>(zstring::memchr(str, ch, str_len));
    }

    ZSIMD_EXPAND inline
    const char* strchr(const char* str, int ch) {
        return zstring::strchr(str, ch, zstring::strlen(str) + 1);
    }


    ZSIMD_EXPAND inline
    char* strchr(char* str, int ch, std::size_t str_len) {
        return const_cast<char*>(zstring::strchr(static_cast<const char*>(str), ch, str_len));
    }

    ZSIMD_EXPAND inline
    char* strchr(char* str, int ch) {
        return const_cast<char*>(zstring::strchr(static_cast<const char*>(str), ch));
    }
}

#endif