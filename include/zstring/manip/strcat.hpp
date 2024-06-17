#ifndef ZSTRING_STRCAT_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcpy.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/manip/strcat.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRCAT_H
#endif


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

#endif