#if !defined(ZSTRING_MEMCPY_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_MEMCPY_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memcpy.hpp"
#include "zsimd/duplicate_foreach.h"
#include "zstring/mem/mem_fn.hpp"

#include <cstring>


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    void* memcpy(void* dest, const void* src, std::size_t i) {
        using simd = zsimd::ZSIMD_ARCH;
        using uchar = unsigned char;
        using vector = simd::vector<uchar>;

        vector cpy = simd::loadu(static_cast<const uchar*>(src) + i);
        simd::storeu(static_cast<uchar*>(dest) + i, cpy);
        return dest;
    }
}
}

namespace zstring {
    ZSIMD_EXPAND inline
    void* memcpy(void* dest, const void* src, std::size_t count) {
        constexpr static std::size_t N = zsimd::ZSIMD_ARCH::vector<unsigned char>::data_size;

        return mem_fn<N>(std::memcpy, zstring::impl::memcpy, count, dest, dest, src);
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif