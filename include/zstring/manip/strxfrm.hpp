#ifndef ZSTRING_STRXFRM_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strxfrm.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRXFRM_H
#endif

#include <cstring>


namespace zstring {
    ZSIMD_EXPAND inline
    std::size_t strxfrm(char* dest, const char* src, std::size_t count) noexcept {
        return std::strxfrm(dest, src, count);
    }
}

#endif