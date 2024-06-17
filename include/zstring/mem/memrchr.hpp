#ifndef ZSTRING_MEMRCHR_H

#ifndef ZSIMD_DUPLICATE_FOREACH

#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memrchr.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_MEMRCHR_H
#endif

#include <cstring>


namespace zstring {
namespace impl {
    ZSIMD_EXPAND inline
    const void* memrchr(const void* ptr, int ch, std::size_t i, std::size_t N) {
        using uchar = unsigned char;
        using simd = zsimd::ZSIMD_ARCH;
        using vector = simd::vector<uchar>;

        vector cmp = simd::eq(simd::loadu(static_cast<const uchar*>(ptr) + i), simd::broadcast<uchar>(ch));
        if(simd::is_all_zeros(cmp)) return nullptr;
        std::size_t idx = simd::countr_zero(simd::to_mask(cmp));
        return static_cast<const uchar*>(ptr) + i + N - idx - 1;
    }
}
}

namespace zstring {
    ZSIMD_EXPAND inline
    const void* memrchr(const void* ptr, int ch, std::size_t count ) {
        using uchar = unsigned char;
        constexpr static std::size_t N = zsimd::ZSIMD_ARCH::vector<uchar>::data_size;

        if(count >= N) goto simd_memrchr;
        
        {
        std::size_t i = count;
        while(i != 0){
            --i;
            if(static_cast<const uchar*>(ptr)[i] == static_cast<uchar>(ch))
                return static_cast<const uchar*>(ptr) + i;
        }
        return nullptr;
        }

        //TODO add support for if count < N but > a smaller vector size

        simd_memrchr:
        {
        std::size_t i = count;
        while(i >= N){
            i -= N;
            const void* ret = zstring::impl::memrchr(ptr, ch, i, N);
            if(ret == nullptr) continue;
            return ret;
        }
        if (i == 0) return nullptr;
        }

        return zstring::impl::memrchr(ptr, ch, 0, N);
    }


    ZSIMD_EXPAND inline
    void* memrchr(void* ptr, int ch, std::size_t count ) {
        return const_cast<void*>(memrchr(static_cast<const void*>(ptr), ch, count));
    }
}

#endif