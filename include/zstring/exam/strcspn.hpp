#ifndef ZSTRING_STRCSPN_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strcspn.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRCSPN_H
#endif
#include "zstring/simd_fn.hpp"
#include "zstring/fn_traits.hpp"

#include <array>
#include <limits>
#include <cstring>


#if defined(__has_builtin) && !defined(ZSTRING_NO_BUILTINS)
#if __has_builtin (__builtin_strcspn) && !defined(__clang__) //clang's strcspn is not constexpr
#define __ZSTRING_BUILTIN_STRCSPN 1
#endif
#endif


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    std::size_t vectorwise_strcspn(const char* dest, const char* src, std::size_t dest_len, std::size_t i) noexcept {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<narrow_type>;

        narrow_type const* needle = src;
        vector haystack = simd::loadu(dest + i);
        vector res = simd::all_zeros<narrow_type>();
        for(; *needle; ++needle)
            res |= simd::eq(haystack, simd::broadcast(*needle));
        if(simd::is_all_zeros(res)) return dest_len;
        return i + simd::countl_zero(simd::to_mask(res));
    }
}
}


namespace zstring {
namespace impl {
    ZSIMD_EXPAND constexpr
    std::size_t naive_strcspn(const char* dest, const char* src, std::size_t dest_len) noexcept {
        #ifdef __ZSTRING_BUILTIN_STRCSPN
        return __builtin_strcspn(dest, src); //TODO length not being used
        #else 
        if(dest_len == 0) return 0;
        std::array<bool, std::numeric_limits<narrow_type>::max()> bad_chars{};
        for(narrow_type const* needle = src; *needle; ++needle)
            bad_chars[*needle] = true;
        for(std::size_t i = 0; i < dest_len; ++i)
            if(bad_chars[dest[i]])
                return i;
        return dest_len;
        #endif
    }

    ZSIMD_EXPAND inline
    std::size_t simd_strcspn(const char* dest, const char* src, std::size_t dest_len) noexcept {
        return impl::ssimd_fn<zsimd::ZSIMD_ARCH, narrow_type>(std::strcspn, vectorwise_strcspn, dest_len, 0, dest_len, dest, src);
    }
}
}


namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    std::size_t strcspn(const char* dest, const char* src, std::size_t dest_len) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(false))
            return impl::naive_strcspn(dest, src, dest_len);
        return impl::simd_strcspn(dest, src, dest_len);
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    std::size_t strcspn(const char* dest, const char* src) noexcept {
        return zstring::strcspn(dest, src, zstring::strlen(dest));
    }


    ZSIMD_EXPAND constexpr
    std::size_t strcspn_constexpr(const char* dest, const char* src, std::size_t dest_len) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(true))
            return impl::naive_strcspn(dest, src, dest_len);
        return impl::simd_strcspn(dest, src, dest_len);
    }

    ZSIMD_EXPAND constexpr
    std::size_t strcspn_constexpr(const char* dest, const char* src) noexcept {
        return zstring::strcspn_constexpr(dest, src, zstring::strlen(dest));
    }
}

#endif