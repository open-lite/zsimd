#ifndef ZSTRING_MEMRCHR_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memrchr.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_MEMRCHR_H
#endif
#include "zstring/simd_fn.hpp"
#include "zstring/fn_traits.hpp"

#include <cstring>


#if defined(__has_builtin) && !defined(ZSTRING_NO_BUILTINS)
#if __has_builtin (__builtin_char_memrchr)
#define __ZSTRING_BUILTIN_MEMRCHR 1
#endif
#endif


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    const narrow_type* vectorwise_memrchr(const narrow_type* ptr, int ch, std::size_t i, std::size_t N) noexcept {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<narrow_type>;

        vector cmp = simd::eq(simd::loadu(reinterpret_cast<const narrow_type*>(ptr) + i), simd::broadcast<narrow_type>(ch));
        if(simd::is_all_zeros(cmp)) return nullptr;
        std::size_t idx = simd::countr_zero(simd::to_mask(cmp));
        return ptr + i + N - idx - 1;
    }
}
}


namespace zstring {
namespace impl {
    ZSIMD_EXPAND constexpr
    const narrow_type* naive_memrchr(const narrow_type* ptr, int ch, std::size_t count) noexcept {
        #ifdef __ZSTRING_BUILTIN_MEMRCHR
        return __builtin_char_memrchr(ptr, ch, count);
        #else 
        if(count == 0) return nullptr;
        std::size_t i = count - 1;
        narrow_type const* p = ptr;
        do {
            if(p[i] == static_cast<narrow_type>(ch))
                return p + i;
        } while(i-- > 0);
        return nullptr;
        #endif
    }

    ZSIMD_EXPAND inline
    const narrow_type* simd_memrchr(const narrow_type* ptr, int ch, std::size_t count) noexcept {
        return impl::rsimd_fn<zsimd::ZSIMD_ARCH, narrow_type>(naive_memrchr, zstring::impl::vectorwise_memrchr, count, static_cast<const narrow_type*>(nullptr), ptr, ch);
    }
}
}


namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    const narrow_type* memrchr(const narrow_type* ptr, int ch, std::size_t count) {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(false))
            return zstring::impl::naive_memrchr(ptr, ch, count);
        return zstring::impl::simd_memrchr(ptr, ch, count);
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    narrow_type* memrchr(narrow_type* ptr, int ch, std::size_t count) {
        return const_cast<narrow_type*>(memrchr(static_cast<const narrow_type*>(ptr), ch, count));
    }


    ZSIMD_EXPAND constexpr
    const narrow_type* memrchr_constexpr(const narrow_type* ptr, int ch, std::size_t count) {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(true))
            return zstring::impl::naive_memrchr(ptr, ch, count);
        return zstring::impl::simd_memrchr(ptr, ch, count);
    }

    ZSIMD_EXPAND constexpr
    narrow_type* memrchr_constexpr(narrow_type* ptr, int ch, std::size_t count) {
        return const_cast<narrow_type*>(memrchr_constexpr(static_cast<const narrow_type*>(ptr), ch, count));
    }
}

#endif