#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcpy.hpp"

#if !defined(ZSTRING_STRCAT_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_STRCAT_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/manip/strcat.hpp"
#include "zsimd/duplicate_foreach.h"


namespace zstring {
    ZSIMD_EXPAND inline
    char* strcat(char* dest, const char* src, std::size_t dest_len, std::size_t src_len) {
        return static_cast<char*>(zstring::memcpy(dest + dest_len, src, src_len + 1));
    }

    ZSIMD_EXPAND inline
    char* strcat(char* dest, const char* src) {
        return zstring::strcat(dest, src, zstring::strlen(dest), zstring::strlen(src));
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif