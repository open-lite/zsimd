#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcpy.hpp"

#if !defined(ZSTRING_STRCPY_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_STRCPY_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/manip/strcpy.hpp"
#include "zsimd/duplicate_foreach.h"


namespace zstring {
    ZSIMD_EXPAND inline
    char* strcpy(char* dest, const char* src, std::size_t len) {
        return static_cast<char*>(zstring::memcpy(dest, src, len + 1));
    }

    ZSIMD_EXPAND inline
    char* strcpy(char* dest, const char* src) {
        return zstring::strcpy(dest, src, zstring::strlen(src));
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif