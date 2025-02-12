#ifndef ZSTRING_STRCOLL_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strcoll.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRCOLL_H
#endif

#include <cstring>


namespace zstring {
    ZSIMD_EXPAND inline
    int strcoll(const char* lhs, const char* rhs) noexcept {
        return std::strcoll(lhs, rhs);
    }
}

#endif