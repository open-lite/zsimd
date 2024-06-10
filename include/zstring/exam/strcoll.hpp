#if !defined(ZSTRING_STRCOLL_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_STRCOLL_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strcoll.hpp"
#include "zsimd/duplicate_foreach.h"

#include <cstring>


namespace zstring {
    ZSIMD_EXPAND inline
    int strcoll(const char* lhs, const char* rhs) {
        return std::strcoll(lhs, rhs);
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif