#ifndef ZSTRING_STRPBRK_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strpbrk.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRPBRK_H
#endif
#include "zstring/simd_fn.hpp"
#include "zstring/fn_traits.hpp"

#include <cstring>


#if defined(__has_builtin) && !defined(ZSTRING_NO_BUILTINS)
#if __has_builtin (__builtin_strpbrk) && !defined(__clang__) //clang's strpbrk is not constexpr
#define __ZSTRING_BUILTIN_STRPBRK 1
#endif
#endif


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    const char* vectorwise_strpbrk(const char* dest, const char* breakset, std::size_t, std::size_t i) noexcept {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<char>;

        char const* needle = breakset;
        vector haystack = simd::loadu(dest + i);
        vector res = simd::all_zeros<char>();
        for(; *needle; ++needle)
            res |= simd::eq(haystack, simd::broadcast(*needle));
        if(simd::is_all_zeros(res)) return nullptr;
        return dest + i + simd::countl_zero(simd::to_mask(res));
    }
}
}


namespace zstring {
namespace impl {
    ZSIMD_EXPAND constexpr
    const char* naive_strpbrk(const char* dest, const char* breakset, std::size_t dest_len) noexcept {
        #ifdef __ZSTRING_BUILTIN_STRPBRK
        return __builtin_strpbrk(dest, breakset);
        #else 
        if(dest_len == 0) return nullptr;
        std::array<bool, std::numeric_limits<narrow_type>::max()> stop_chars{};
        for(narrow_type const* needle = breakset; *needle; ++needle)
            stop_chars[*needle] = true;
        for(std::size_t i = 0; i < dest_len; ++i)
            if(stop_chars[dest[i]])
                return &dest[i];
        return nullptr;
        #endif
    }

    ZSIMD_EXPAND inline
    const char* simd_strpbrk(const char* dest, const char* breakset, std::size_t dest_len) noexcept {
        return impl::ssimd_fn<zsimd::ZSIMD_ARCH, narrow_type>(static_cast<const char*(&)(const char*, const char*)>(std::strpbrk), 
            vectorwise_strpbrk, dest_len, 0, static_cast<const char*>(nullptr), dest, breakset);
    }
}
}

namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    const char* strpbrk(const char* dest, const char* breakset, std::size_t dest_len) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(false))
            return impl::naive_strpbrk(dest, breakset, dest_len);
        return impl::simd_strpbrk(dest, breakset, dest_len);
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    const char* strpbrk(const char* dest, const char* breakset) noexcept {
        return zstring::strpbrk(dest, breakset, zstring::strlen(dest));
    }


    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strpbrk(char* dest, const char* breakset, std::size_t dest_len) noexcept {
        return const_cast<char*>(zstring::strpbrk(static_cast<const char*>(dest), breakset, dest_len));
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strpbrk(char* dest, const char* breakset) noexcept {
        return const_cast<char*>(zstring::strpbrk(static_cast<const char*>(dest), breakset));
    }
}

namespace zstring {
    ZSIMD_EXPAND constexpr
    const char* strpbrk_constexpr(const char* dest, const char* breakset, std::size_t dest_len) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(true))
            return impl::naive_strpbrk(dest, breakset, dest_len);
        return impl::simd_strpbrk(dest, breakset, dest_len);
    }

    ZSIMD_EXPAND constexpr
    const char* strpbrk_constexpr(const char* dest, const char* breakset) noexcept {
        return zstring::strpbrk_constexpr(dest, breakset, zstring::strlen(dest));
    }


    ZSIMD_EXPAND constexpr
    char* strpbrk_constexpr(char* dest, const char* breakset, std::size_t dest_len) noexcept {
        return const_cast<char*>(zstring::strpbrk_constexpr(static_cast<const char*>(dest), breakset, dest_len));
    }

    ZSIMD_EXPAND constexpr
    char* strpbrk_constexpr(char* dest, const char* breakset) noexcept {
        return const_cast<char*>(zstring::strpbrk_constexpr(static_cast<const char*>(dest), breakset));
    }
}

#endif