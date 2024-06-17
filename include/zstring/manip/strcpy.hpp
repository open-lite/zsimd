#ifndef ZSTRING_STRCPY_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcpy.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/manip/strcpy.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRCPY_H
#endif


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

#endif