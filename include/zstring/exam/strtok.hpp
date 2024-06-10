#include "zstring/exam/strspn.hpp"
#include "zstring/exam/strcspn.hpp"

#if !defined(ZSTRING_STRTOK_H) || defined(ZSIMD_DUPLICATE_FOREACH)
#define ZSTRING_STRTOK_H
#define ZSIMD_SELF_INCLUDE_PATH "zstring/exam/strtok.hpp"
#include "zsimd/duplicate_foreach.h"


namespace zstring {
    ZSIMD_EXPAND inline
    char* strtok(char* str, const char* delim) {
        static char* buffer;
    
        if (str) buffer = str;
        buffer += zstring::strspn(buffer, delim);
    
        if (!*buffer) return nullptr;

        char* const begin = buffer;
    
        buffer += zstring::strcspn(buffer, delim);
    
        if (*buffer) *(buffer++) = '\0';
        
        return begin;
    }
}

#undef ZSIMD_SELF_INCLUDE_PATH
#endif