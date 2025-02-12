#ifndef ZSTRING_MEMMOVE_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/mem/memcpy.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memmove.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_MEMMOVE_H
#endif
#include "zstring/fn_traits.hpp"


namespace zstring {
    ZSIMD_EXPAND __ZSTRING_CONSTEXPR_EVAL_FN
    narrow_type* memmove(narrow_type* dest, const narrow_type* src, std::size_t count) noexcept {
        if(dest == src || count == 0) return dest;
        narrow_type* tmp = new narrow_type[count];
        zstring::memcpy(tmp, src, count);
        zstring::memcpy(dest, tmp, count);
        delete[] tmp;
        return dest;
    }

    //naive constexpr version of memmove is possible but has much more complex implemntation than just dma and memcpy
    //ZSIMD_EXPAND constexpr
    //void* memcpy_constexpr(void* dest, const void* src, std::size_t count) noexcept;
}

#endif