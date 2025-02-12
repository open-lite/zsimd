#ifndef ZSTRING_MEMCPY_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memcpy.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_MEMCPY_H
#endif
#include "zstring/simd_fn.hpp"
#include "zstring/fn_traits.hpp"

#include <cstring>


#if defined(__has_builtin) && !defined(ZSTRING_NO_BUILTINS)
#if __has_builtin (__builtin_char_memcpy)
#define __ZSTRING_BUILTIN_MEMCPY 1
#endif
#endif


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    narrow_type* vectorwise_memcpy(narrow_type* dest, const narrow_type* src, std::size_t i) noexcept {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<narrow_type>;

        vector cpy = simd::loadu(src + i);
        simd::storeu(dest + i, cpy);
        return dest;
    }
}
}


namespace zstring {
namespace impl {
    ZSIMD_EXPAND constexpr
    narrow_type* naive_memcpy(narrow_type* dest, const narrow_type* src, std::size_t count) noexcept {
        #ifdef __ZSTRING_BUILTIN_MEMCPY
        return __builtin_char_memcpy(dest, src, count);
        #else 
        if(count == 0) return dest;
        narrow_type* d = dest;
        narrow_type const* s = src;
        for(std::size_t i = 0; i < count; ++i) d[i] = s[i];
        return dest;
        #endif
    }

    ZSIMD_EXPAND inline
    narrow_type* simd_memcpy(narrow_type* dest, const narrow_type* src, std::size_t count) noexcept {
        return impl::simd_fn<zsimd::ZSIMD_ARCH, narrow_type>(std::memcpy, vectorwise_memcpy, count, dest, dest, src);
    }
}
}

namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    narrow_type* memcpy(narrow_type* dest, const narrow_type* src, std::size_t count) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(false))
            return zstring::impl::naive_memcpy(dest, src, count);
        return zstring::impl::simd_memcpy(dest, src, count);
    }


    ZSIMD_EXPAND constexpr
    narrow_type* memcpy_constexpr(narrow_type* dest, const narrow_type* src, std::size_t count) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(true))
            return zstring::impl::naive_memcpy(dest, src, count);
        return zstring::impl::simd_memcpy(dest, src, count);
    }
}

#endif