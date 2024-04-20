#pragma once

#ifndef ZSIMD_TARGET
#define ZSIMD_TARGET(...) [[gnu::target(#__VA_ARGS__)]]
#define __ZSIMD_EVAL_TARGET(x) ZSIMD_TARGET(x)
#endif