#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcpy.hpp"

#if !defined(ZSTRING_STRNCAT_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_STRNCAT_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/manip/strncat.hpp"
#include "zsimd/duplicate_foreach.h"


namespace zstring {
    ZSIMD_EXPAND inline
    char* strncat(char* dest, const char* src, std::size_t count, std::size_t dest_len, std::size_t src_len) {
        return static_cast<char*>(zstring::memcpy(dest + dest_len, src, std::min(src_len + 1, count)));
    }

    ZSIMD_EXPAND inline
    char* strncat(char* dest, const char* src, std::size_t count) {
        return zstring::strncat(dest, src, count, zstring::strlen(dest), zstring::strlen(src));
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif