#ifndef ZSTRING_MEMCHR_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memchr.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_MEMCHR_H
#endif
#include "zstring/mem/mem_fn.hpp"

#include <cstring>


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    const void* memchr(const void* ptr, int ch, std::size_t i) {
        using simd = zsimd::ZSIMD_ARCH;
        using uchar = unsigned char;
        using vector = simd::vector<uchar>;

        vector cmp = simd::eq(simd::loadu(static_cast<const uchar*>(ptr) + i), simd::broadcast<uchar>(ch));
        if(simd::is_all_zeros(cmp)) return nullptr;
        std::size_t idx = simd::countl_zero(simd::to_mask(cmp));
        return static_cast<const uchar*>(ptr) + i + idx;
    }
}
}

namespace zstring {
    ZSIMD_EXPAND inline
    const void* memchr(const void* ptr, int ch, std::size_t count) {
        constexpr static std::size_t N = zsimd::ZSIMD_ARCH::vector<unsigned char>::data_size;

        return mem_fn<N>(static_cast<const void*(*)(const void*, int, std::size_t)>(std::memchr), 
            zstring::impl::memchr, count, static_cast<const void*>(nullptr), ptr, ch);
    }


    ZSIMD_EXPAND inline
    void* memchr(void* ptr, int ch, std::size_t count ) {
        return const_cast<void*>(memchr(static_cast<const void*>(ptr), ch, count));
    }
}

#endif