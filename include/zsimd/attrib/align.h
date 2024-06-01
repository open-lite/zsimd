#pragma once

#ifndef ZSIMD_ALIGN(arch, type)
#define ZSIMD_ALIGN(arch, type) alignas(arch::vector<type>::total_size)
#endif