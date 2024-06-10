#if !defined(ZSTRING_STRLEN_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_STRLEN_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strlen.hpp"
#include "zsimd/duplicate_foreach.h"

#include <cstring>
#include <cstddef>


namespace zstring {
    ZSIMD_EXPAND inline
    std::size_t strlen(const char* str) {
        return std::strlen(str);
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif