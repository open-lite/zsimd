#ifndef ZSTRING_MEMSET_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memset.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_MEMSET_H
#endif
#include "zstring/simd_fn.hpp"
#include "zstring/fn_traits.hpp"

#include <cstring>


#if defined(__has_builtin) && !defined(ZSTRING_NO_BUILTINS)
#if __has_builtin (__builtin_char_memset)
#define __ZSTRING_BUILTIN_MEMSET 1
#endif
#endif


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    narrow_type* vectorwise_memset(narrow_type* dest, int ch, std::size_t i) noexcept {
        using simd = zsimd::ZSIMD_ARCH;
        simd::storeu(dest + i, simd::broadcast(static_cast<narrow_type>(ch)));
        return dest;
    }
}
}


namespace zstring {
namespace impl {
    ZSIMD_EXPAND constexpr
    narrow_type* naive_memset(narrow_type* dest, int ch, std::size_t count) noexcept {
        #ifdef __ZSTRING_BUILTIN_MEMSET
        return __builtin_char_memset(dest, ch, count);
        #else 
        if(count == 0) return dest;
        narrow_type* d = dest;
        for(std::size_t i = 0; i < count; ++i) d[i] = static_cast<narrow_type>(ch);
        return dest;
        #endif
    }

    ZSIMD_EXPAND inline
    narrow_type* simd_memset(narrow_type* dest, int ch, std::size_t count) noexcept {
        return impl::simd_fn<zsimd::ZSIMD_ARCH, narrow_type>(std::memset, vectorwise_memset, count, dest, dest, ch);
    }
}
}

namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    narrow_type* memset(narrow_type* dest, int ch, std::size_t count) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(false))
            return zstring::impl::naive_memset(dest, ch, count);
        return zstring::impl::simd_memset(dest, ch, count);
    }


    ZSIMD_EXPAND constexpr
    narrow_type* memset_constexpr(narrow_type* dest, int ch, std::size_t count) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(true))
            return zstring::impl::naive_memset(dest, ch, count);
        return zstring::impl::simd_memset(dest, ch, count);
    }
}

#endif