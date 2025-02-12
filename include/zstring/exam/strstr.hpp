#ifndef ZSTRING_STRSTR_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strlen.hpp"
#include "zstring/mem/memcmp.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strstr.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRSTR_H
#endif
#include "zstring/fn_traits.hpp"

#include <cstring>


#if defined(__has_builtin) && !defined(ZSTRING_NO_BUILTINS)
#if __has_builtin (__builtin_strstr) && !defined(__clang__) //clang's strstr is not constexpr
#define __ZSTRING_BUILTIN_STRSTR 1
#endif
#endif



namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    const char* std_strstr(const char* haystack, const char* needle, void const*, void const*, std::size_t) noexcept {
        return std::strstr(haystack, needle); //NOTE doesn't optimize based on length
    }

    ZSIMD_EXPAND inline
    const char* vectorwise_strstr(const char* haystack, const char* needle, void const* needle_first_ptr, void const* needle_last_ptr, std::size_t needle_len, std::size_t, std::size_t i) noexcept {
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<narrow_type>;
        using mask = simd::mask<narrow_type>;

        vector const* needle_first = static_cast<vector const*>(needle_first_ptr);
        vector const* needle_last  = static_cast<vector const*>(needle_last_ptr);

        vector eq_first = simd::eq(simd::loadu(haystack + i), *needle_first);
        vector eq_last  = simd::eq(simd::loadu(haystack + i + needle_len - 1), *needle_last);
        vector needles  = simd::bitwise_and(eq_first, eq_last);

        if(simd::is_all_zeros(needles)) return nullptr;
        mask needle_mask = simd::to_mask(needles);
        while(needle_mask) {
            std::size_t needle_idx = simd::countl_zero(needle_mask);
            if(zstring::memcmp(haystack + i + needle_idx + 1, needle + 1, needle_len - 2) == 0)
                return haystack + i + needle_idx;
            needle_mask &= simd::right_mask<true, char>(needle_idx + 1);
        }
        return nullptr;
    }
}
}


namespace zstring {
namespace impl {
    ZSIMD_EXPAND constexpr
    const char* naive_strstr(const char* haystack, const char* needle, std::size_t haystack_len, std::size_t needle_len) noexcept {
        #ifdef __ZSTRING_BUILTIN_STRSTR
        return __builtin_strstr(haystack, needle);
        #else 
        if(haystack_len == 0 || needle_len > haystack_len) return nullptr;
        if(needle_len == 0) return haystack;
        for(std::size_t i = 0; i < haystack_len; ++i)
            if(zstring::memcmp(&haystack[i], needle, needle_len) == 0)
                return &haystack[i];
        return nullptr;
        #endif
    }

    ZSIMD_EXPAND inline
    const char* simd_strstr(const char* haystack, const char* needle, std::size_t haystack_len, std::size_t needle_len) noexcept {
        if(needle_len > haystack_len) return nullptr;
        if(needle_len == 0) return haystack;

        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<narrow_type>;
        vector needle_first = simd::broadcast(needle[0]);
        vector needle_last  = simd::broadcast(needle[needle_len - 1]);
        return impl::ssimd_fn<zsimd::ZSIMD_ARCH, narrow_type>(std_strstr, vectorwise_strstr, haystack_len, needle_len - 1, static_cast<const char*>(nullptr), 
            haystack, needle, &needle_first, &needle_last, needle_len);
    }
}
}


namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    const char* strstr(const char* haystack, const char* needle, std::size_t haystack_len, std::size_t needle_len) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(false))
            return impl::naive_strstr(haystack, needle, haystack_len, needle_len);
        return impl::simd_strstr(haystack, needle, haystack_len, needle_len);
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    const char* strstr(const char* haystack, const char* needle) noexcept {
        return zstring::strstr(haystack, needle, zstring::strlen(haystack), zstring::strlen(needle));
    }


    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strstr(char* haystack, const char* needle, std::size_t haystack_len, std::size_t needle_len) noexcept {
        return const_cast<char*>(zstring::strstr(static_cast<const char*>(haystack), needle, haystack_len, needle_len));
    }

    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    char* strstr(char* haystack, const char* needle) noexcept {
        return const_cast<char*>(zstring::strstr(static_cast<const char*>(haystack), needle));
    }
}

namespace zstring {
    ZSIMD_EXPAND constexpr
    const char* strstr_constexpr(const char* haystack, const char* needle, std::size_t haystack_len, std::size_t needle_len) noexcept {
        if(__ZSTRING_IS_CONSTEXPR_EVAL(true))
            return impl::naive_strstr(haystack, needle, haystack_len, needle_len);
        return impl::simd_strstr(haystack, needle, haystack_len, needle_len);
    }

    ZSIMD_EXPAND constexpr
    const char* strstr_constexpr(const char* haystack, const char* needle) noexcept {
        return zstring::strstr_constexpr(haystack, needle, zstring::strlen(haystack), zstring::strlen(needle));
    }


    ZSIMD_EXPAND constexpr
    char* strstr_constexpr(char* haystack, const char* needle, std::size_t haystack_len, std::size_t needle_len) noexcept {
        return const_cast<char*>(zstring::strstr_constexpr(static_cast<const char*>(haystack), needle, haystack_len, needle_len));
    }

    ZSIMD_EXPAND constexpr
    char* strstr_constexpr(char* haystack, const char* needle) noexcept {
        return const_cast<char*>(zstring::strstr_constexpr(static_cast<const char*>(haystack), needle));
    }
}

#endif