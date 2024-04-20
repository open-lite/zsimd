#pragma once

#ifndef ZSIMD_CURRENT_ARCH

#if   defined(__x86_64__) || defined(__amd64) || defined(_M_X64) || defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#define ZSIMD_CURRENT_ARCH x86
#define ZSIMD_X86 1
#elif defined(__arm__) || defined(__TARGET_ARCH_ARM) || defined(_M_ARM) || defined(__aarch64__)
#define ZSIMD_CURRENT_ARCH ARM
#define ZSIMD_ARM 1
#elif defined(__ppc__) || defined(__ppc) || defined(__powerpc__)
#define ZSIMD_CURRENT_ARCH PowerPC
#define ZSIMD_POWERPC 1
#elif defined(__riscv__) || defined(_riscv) || defined(__riscv32)
#define ZSIMD_CURRENT_ARCH RISC-V
#define ZSIMD_RISCV 1
#else
#error Unable to detect CPU architecture family
#endif

#endif