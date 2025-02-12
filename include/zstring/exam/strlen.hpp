#ifndef ZSTRING_STRLEN_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strlen.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRLEN_H
#endif
#include "zstring/fn_traits.hpp"

#include <cstring>
#include <cstddef>


#if defined(__has_builtin) && !defined(ZSTRING_NO_BUILTINS)
#if __has_builtin (__builtin_strlen)
#define __ZSTRING_BUILTIN_STRLEN 1
#endif
#endif


namespace zstring {
    ZSIMD_EXPAND constexpr
    std::size_t strlen(const char* str) noexcept {
        #ifdef __ZSTRING_BUILTIN_STRLEN
        return __builtin_strlen(str);
        #else
        char const* s = str;
        for (; *s; ++s);
        return (s - str);
        #endif
    }
}

#endif