#ifndef ZSTRING_MEMCMP_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memcmp.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_MEMCMP_H
#endif
#include "zstring/simd_fn.hpp"
#include "zstring/fn_traits.hpp"

#include <cstring>
#include <type_traits>


#if defined(__has_builtin) && !defined(ZSTRING_NO_BUILTINS)
#if __has_builtin (__builtin_memcmp)
#define __ZSTRING_BUILTIN_MEMCMP 1
#endif
#endif


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    int vectorwise_memcmp(const narrow_type* lhs, const narrow_type* rhs, std::size_t i) noexcept {
        using simd = zsimd::ZSIMD_ARCH;
        using schar = std::make_signed_t<narrow_type>; //using char instead of unsigned char to use signed subtraction
        using mask = simd::mask<schar>;
        using vector = simd::vector<schar>;

        vector diff = simd::sub(simd::loadu(reinterpret_cast<const schar*>(lhs) + i), simd::loadu(reinterpret_cast<const schar*>(rhs) + i));
        if(simd::is_all_zeros(diff)) return 0;
        mask m = simd::to_mask(simd::eq(diff, simd::all_zeros<schar>()));
        std::size_t idx = simd::countl_one(m);
        return simd::to_array(diff)[idx];
    }
}
}


namespace zstring {
namespace impl {
    ZSIMD_EXPAND constexpr
    int naive_memcmp(const narrow_type* lhs, const narrow_type* rhs, std::size_t count) noexcept {
        #ifdef __ZSTRING_BUILTIN_MEMCMP
        return __builtin_memcmp(lhs, rhs, count);
        #else 
        if(count == 0) return 0;
        narrow_type const* l = lhs;
        narrow_type const* r = rhs;
        using schar = std::make_signed_t<narrow_type>; 
        for (std::size_t i = 0; i < count; ++i)
            if(lhs[i] != rhs[i])
                return static_cast<schar>(lhs[i]) - static_cast<schar>(rhs[i]);
        return 0;
        #endif
    }

    ZSIMD_EXPAND inline
    int simd_memcmp(const narrow_type* lhs, const narrow_type* rhs, std::size_t count) noexcept {
        return impl::simd_fn<zsimd::ZSIMD_ARCH, narrow_type>(std::memcmp, vectorwise_memcmp, count, 0, lhs, rhs);
    }
}
}

namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    int memcmp(const narrow_type* lhs, const narrow_type* rhs, std::size_t count) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(false))
            return zstring::impl::naive_memcmp(lhs, rhs, count);
        return zstring::impl::simd_memcmp(lhs, rhs, count);
    }


    ZSIMD_EXPAND constexpr
    int memcmp_constexpr(const narrow_type* lhs, const narrow_type* rhs, std::size_t count) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(true))
            return zstring::impl::naive_memcmp(lhs, rhs, count);
        return zstring::impl::simd_memcmp(lhs, rhs, count);
    }
}

#endif