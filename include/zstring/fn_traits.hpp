#pragma once
#include <cstddef>

#if __cpp_lib_is_constant_evaluated >= 201811L
#define __ZSTRING_CONSTEXPR_EVAL_FN constexpr
#define __ZSTRING_IS_CONSTEXPR_EVAL(_) std::is_constant_evaluated()
#else
#define __ZSTRING_CONSTEXPR_EVAL_FN inline
#define __ZSTRING_IS_CONSTEXPR_EVAL(fallback) fallback
#endif


namespace zstring {
    using narrow_type = char;
    using wide_type = wchar_t;

    //#if __cpp_lib_byte >= 201603L
    //using byte_type = std::byte;
    //#endif 
}