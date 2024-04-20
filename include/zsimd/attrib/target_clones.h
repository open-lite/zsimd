#pragma once

//currently supported and enabled architectures
#ifdef ZSIMD_X86
    #define ZSIMD_TARGET_CLONES [[gnu::target_clones("default")]]
#endif