#ifndef ZSTRING_STRLEN_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strlen.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRLEN_H
#endif

#include <cstring>
#include <cstddef>


namespace zstring {
    ZSIMD_EXPAND inline
    std::size_t strlen(const char* str) {
        return std::strlen(str);
    }
}

#endif