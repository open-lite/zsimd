#ifndef ZSTRING_MEMCHR_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memchr.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_MEMCHR_H
#endif
#include "zstring/simd_fn.hpp"
#include "zstring/fn_traits.hpp"

#include <cstring>


#if defined(__has_builtin) && !defined(ZSTRING_NO_BUILTINS)
#if __has_builtin (__builtin_char_memchr)
#define __ZSTRING_BUILTIN_MEMCHR 1
#endif
#endif


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    const narrow_type* vectorwise_memchr(const narrow_type* ptr, int ch, std::size_t i) noexcept {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<narrow_type>;

        vector cmp = simd::eq(simd::loadu(reinterpret_cast<const narrow_type*>(ptr) + i), simd::broadcast<narrow_type>(ch));
        if(simd::is_all_zeros(cmp)) return nullptr;
        std::size_t idx = simd::countl_zero(simd::to_mask(cmp));
        return ptr + i + idx;
    }
}
}


namespace zstring {
namespace impl {
    ZSIMD_EXPAND constexpr
    const narrow_type* naive_memchr(const narrow_type* ptr, int ch, std::size_t count) noexcept {
        #ifdef __ZSTRING_BUILTIN_MEMCHR
        return __builtin_char_memchr(ptr, ch, count);
        #else 
        if(count == 0) return dest;
        narrow_type const* p = ptr;
        for (std::size_t i = 0; i < count; ++i)
            if(p[i] == static_cast<narrow_type>(c))
                return p + i;
        return nullptr;
        #endif
    }
    
    ZSIMD_EXPAND inline
    const narrow_type* simd_memchr(const narrow_type* ptr, int ch, std::size_t count) noexcept {
        return impl::simd_fn<zsimd::ZSIMD_ARCH, narrow_type>(static_cast<const void*(&)(const void*, int, std::size_t) noexcept>(std::memchr), 
            vectorwise_memchr, count, static_cast<const narrow_type*>(nullptr), ptr, ch);
    }
}
}

namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    const narrow_type* memchr(const narrow_type* ptr, int ch, std::size_t count) {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(false))
            return zstring::impl::naive_memchr(ptr, ch, count);
        return zstring::impl::simd_memchr(ptr, ch, count);
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    narrow_type* memchr(narrow_type* ptr, int ch, std::size_t count) {
        return const_cast<narrow_type*>(memchr(static_cast<const narrow_type*>(ptr), ch, count));
    }


    ZSIMD_EXPAND constexpr
    const narrow_type* memchr_constexpr(const narrow_type* ptr, int ch, std::size_t count) {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(true))
            return zstring::impl::naive_memchr(ptr, ch, count);
        return zstring::impl::simd_memchr(ptr, ch, count);
    }

    ZSIMD_EXPAND constexpr
    narrow_type* memchr_constexpr(narrow_type* ptr, int ch, std::size_t count) {
        return const_cast<narrow_type*>(memchr_constexpr(static_cast<const narrow_type*>(ptr), ch, count));
    }
}

#endif