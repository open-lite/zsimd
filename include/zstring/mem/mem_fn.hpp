#pragma once
#include <cstddef>
#include <utility>


//Removes code duplication in mem functions 
//(essentially by running each "loop" function every N chunks)
//
//Generated assembly should be near identical 
//(it is 100% identical in memset, memcpy, and memmove) 
//compared to writing them out manually, so this is better than a macro
template<std::size_t N, typename StlFn, typename LoopFn, typename RetT, typename... Args>
RetT mem_fn(StlFn&& stl, LoopFn&& loop, std::size_t count, RetT fail_value, Args&&... args) {
    if(count < N) return std::forward<StlFn>(stl)(std::forward<Args>(args)..., count);

    //TODO add support for if count < N but > a smaller vector size

    {
    std::size_t i = 0;
    for(; i + N <= count; i += N) {
        RetT ret = std::forward<LoopFn>(loop)(std::forward<Args>(args)..., i);
        if(ret == fail_value) continue;
        return ret;
    }
    if (i >= count) return fail_value;
    }

    std::size_t inc = count - N;
    return std::forward<LoopFn>(loop)(std::forward<Args>(args)..., inc);
}
