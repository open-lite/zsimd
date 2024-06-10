#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcpy.hpp"
#include "zstring/mem/memset.hpp"

#if !defined(ZSTRING_STRNCPY_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_STRNCPY_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/manip/strncpy.hpp"
#include "zsimd/duplicate_foreach.h"


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

#undef ZSIMD_SELF_INCLUDE_PATH
#endif