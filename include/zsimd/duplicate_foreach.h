#ifndef __ZSIMD_DUPLICATE
#define __ZSIMD_DUPLICATE
#include "zsimd/attrib/current_arch.h"


#undef ZSIMD_ARCH_TARGET
#define ZSIMD_ARCH_TARGET ZSIMD_ARCH
#define __ZSIMD_EXPAND_FILE "zsimd/attrib/expand.h"


/** x86 **/
#ifdef ZSIMD_X86
    //SSE
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH sse
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH

    //SSE2
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH sse2
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH

    //SSE3
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH sse3
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH

    //SSSE3
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH ssse3
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH

    //SSE4
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH sse4
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH

    //SSE4a
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH sse4a
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH


    #undef ZSIMD_ARCH_TARGET

    //SSE4.1
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH sse4_1
    #define ZSIMD_ARCH_TARGET sse4.1
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH

    //SSE4.2
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH sse4_2
    #define ZSIMD_ARCH_TARGET sse4.2
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH

    #define ZSIMD_ARCH_TARGET ZSIMD_ARCH


    //AVX
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH avx
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH

    //AVX2
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH avx2
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH


    //AVX512f
    #undef ZSIMD_ARCH
    #define ZSIMD_ARCH avx512f
    #include __ZSIMD_EXPAND_FILE
    #include ZSIMD_SELF_INCLUDE_PATH

/** ARM Neon/SVE **/
#elif ZSIMD_ARM
/** PowerPC **/
#elif ZSIMD_POWERPC
/** RISC-V **/
#elif ZSIMD_RISCV
#endif


/** Scalar **/
#undef ZSIMD_ARCH
#undef ZSIMD_ARCH_TARGET
#include "expand.h"


#undef __ZSIMD_DUPLICATE
#endif