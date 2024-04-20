#include "zsimd/attrib/target.h"

#if !defined(__ZSIMD_STRINGIFY) || !defined(__ZSIMD_INCLUDE)
#define __ZSIMD_STRINGIFY(x) #x
#define __ZSIMD_INCLUDE(file) __ZSIMD_STRINGIFY(zsimd/impl/file.hpp)
#endif

#ifndef ZSIMD_ARCH
#define ZSIMD_ARCH scalar
#define ZSIMD_ARCH_TARGET default
#endif

#undef ZSIMD_EXPAND
#define ZSIMD_EXPAND __ZSIMD_EVAL_TARGET(ZSIMD_ARCH_TARGET)
#include __ZSIMD_INCLUDE(ZSIMD_ARCH)