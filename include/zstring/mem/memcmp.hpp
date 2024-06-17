#ifndef ZSTRING_MEMCMP_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memcmp.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_MEMCMP_H
#endif
#include "zstring/mem/mem_fn.hpp"

#include <cstring>


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    int memcmp(const void* lhs, const void* rhs, std::size_t i) {
        using simd = zsimd::ZSIMD_ARCH;
        using uchar = char; //using char instead of unsigned char to use signed subtraction
        using mask = simd::mask<uchar>;
        using vector = simd::vector<uchar>;

        vector diff = simd::sub(simd::loadu(static_cast<const uchar*>(lhs) + i), simd::loadu(static_cast<const uchar*>(rhs) + i));
        if(simd::is_all_zeros(diff)) return 0;
        mask m = simd::to_mask(simd::eq(diff, simd::all_zeros<uchar>()));
        std::size_t idx = simd::countl_one(m);
        return simd::to_array(diff)[idx];
    }
}
}

namespace zstring {
    ZSIMD_EXPAND inline
    int memcmp(const void* lhs, const void* rhs, std::size_t count) {
        constexpr static std::size_t N = zsimd::ZSIMD_ARCH::vector<char>::data_size;

        return mem_fn<N>(std::memcmp, zstring::impl::memcmp, count, 0, lhs, rhs);
    }
}

#endif