#ifndef ZSTRING_MEMSET_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memset.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_MEMSET_H
#endif
#include "zstring/mem/mem_fn.hpp"

#include <cstring>

namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    void* memset(void* dest, int ch, std::size_t i) {
        using simd = zsimd::ZSIMD_ARCH;
        using uchar = unsigned char;
        simd::storeu(static_cast<uchar*>(dest) + i, simd::broadcast(static_cast<unsigned char>(ch)));
        return dest;
    }
}
}

namespace zstring {
    ZSIMD_EXPAND inline
    void* memset(void* dest, int ch, std::size_t count) {
        using simd = zsimd::ZSIMD_ARCH;
        using uchar = unsigned char;
        using vector = simd::vector<uchar>;
        constexpr static std::size_t N = zsimd::ZSIMD_ARCH::vector<unsigned char>::data_size;

        return mem_fn<N>(std::memset, zstring::impl::memset, count, dest, dest, ch);
    }
}

#endif