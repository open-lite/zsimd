#include "zstring/mem/memcpy.hpp"

#if !defined(ZSTRING_MEMMOVE_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_MEMMOVE_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/mem/memmove.hpp"
#include "zsimd/duplicate_foreach.h"


namespace zstring {
    ZSIMD_EXPAND inline
    void* memmove(void* dest, const void* src, std::size_t count) {
        constexpr static std::size_t N = zsimd::ZSIMD_ARCH::vector<unsigned char>::data_size;

        if(count < N) return std::memmove(dest, src, count);

        unsigned char* tmp = new unsigned char[count];
        zstring::memcpy(tmp, src, count);
        zstring::memcpy(dest, tmp, count);
        delete[] tmp;
        return dest;
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif