#ifndef ZSTRING_STRNCPY_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcpy.hpp"
#include "zstring/mem/memset.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/manip/strncpy.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRNCPY_H
#endif


namespace zstring {
    ZSIMD_EXPAND inline
    char* strncpy(char* dest, const char* src, std::size_t count, std::size_t src_len) {
        if(count < src_len) return static_cast<char*>(zstring::memcpy(dest, src, count));
        zstring::memcpy(dest, src, src_len);
        zstring::memset(dest + src_len, 0, count - src_len);
        return dest;
    }

    ZSIMD_EXPAND inline
    char* strncpy(char* dest, const char* src, std::size_t count) {
        return zstring::strncpy(dest, src, count, zstring::strlen(src));
    }
}

#endif