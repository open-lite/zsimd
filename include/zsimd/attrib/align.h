#pragma once

#ifndef ZSIMD_ALIGN(arch, type)
#define ZSIMD_ALIGN(arch, type) alignas(arch::vector<type>::native_size)
#endif