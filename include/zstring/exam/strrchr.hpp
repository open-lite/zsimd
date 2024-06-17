#ifndef ZSTRING_STRRCHR_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memrchr.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strrchr.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRRCHR_H
#endif


namespace zstring {
    ZSIMD_EXPAND inline
    const char* strrchr(const char* str, int ch, std::size_t str_len) {
        return static_cast<const char*>(zstring::memrchr(str, ch, str_len));
    }

    ZSIMD_EXPAND inline
    const char* strrchr(const char* str, int ch) {
        return zstring::strrchr(str, ch, zstring::strlen(str) + 1);
    }


    ZSIMD_EXPAND inline
    char* strrchr(char* str, int ch, std::size_t str_len) {
        return const_cast<char*>(zstring::strrchr(static_cast<const char*>(str), ch, str_len));
    }

    ZSIMD_EXPAND inline
    char* strrchr(char* str, int ch) {
        return const_cast<char*>(zstring::strrchr(static_cast<const char*>(str), ch));
    }
}

#endif