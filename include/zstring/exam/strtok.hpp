#ifndef ZSTRING_STRTOK_H

#ifndef ZSIMD_DUPLICATE_FOREACH
#include "zstring/exam/strspn.hpp"
#include "zstring/exam/strcspn.hpp"

#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strtok.hpp"
#include "zsimd/duplicate_foreach.h"
#undef ZSIMD_SELF_INCLUDE_PATH

#define ZSTRING_STRTOK_H
#endif


namespace zstring {
    //TODO create non-static version that returns all tokens at once (i.e. string split)?
    ZSIMD_EXPAND inline
    char* strtok(char* str, const char* delim) noexcept {
        static char* buffer;
    
        if (str) buffer = str;
        buffer += zstring::strspn(buffer, delim);
    
        if (!*buffer) return nullptr;

        char* const begin = buffer;
    
        buffer += zstring::strcspn(buffer, delim);
    
        if (*buffer) *(buffer++) = '\0';
        
        return begin;
    }


    //TODO create constexpr version (can't use static variable in constexpr function before c++23)
    //ZSIMD_EXPAND constexpr
    //char* strtok_constexpr(char* str, const char* delim) noexcept;
}

#endif