#if !defined(ZSTRING_STRXFRM_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_STRXFRM_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strxfrm.hpp"
#include "zsimd/duplicate_foreach.h"

#include <cstring>


namespace zstring {
    ZSIMD_EXPAND inline
    std::size_t strxfrm(char* dest, const char* src, std::size_t count) {
        return std::strxfrm(dest, src, count);
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif