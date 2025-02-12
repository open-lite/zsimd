#pragma once
#include <cstddef>
#include <utility>


namespace zstring{ 
namespace impl {
    //Removes code duplication in mem functions 
    //(essentially by running each "loop" function every N chunks)
    //
    //Generated assembly should be near identical 
    //(it is 100% identical in memset, memcpy, and memmove) 
    //compared to writing them out manually, so this is better than a macro
    template<typename Arch, typename DataT, typename StlFn, typename LoopFn, typename RetT, typename... Args>
    constexpr RetT simd_fn(StlFn&& stl, LoopFn&& loop, std::size_t count, RetT fail_value, Args&&... args) noexcept {
        constexpr std::size_t N = Arch::template vector<DataT>::slots;
        if(count < N) return reinterpret_cast<RetT>(std::forward<StlFn>(stl)(std::forward<Args>(args)..., count));

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

        return std::forward<LoopFn>(loop)(std::forward<Args>(args)..., (count - N));
    }
}
}


namespace zstring{ 
namespace impl {
    //same as simd_fn but passes count to LoopFn instead of StlFn
    //Designed for str functions instead of mem functions
    template<typename Arch, typename DataT, typename StlFn, typename LoopFn, typename RetT, typename... Args>
    constexpr RetT ssimd_fn(StlFn&& stl, LoopFn&& loop, std::size_t dest_count, std::size_t src_count, RetT fail_value, Args&&... args) noexcept {
        constexpr std::size_t N = Arch::template vector<DataT>::slots;
        //TODO use string functions that factor in and optimize using count?
        if(dest_count + src_count < N) return reinterpret_cast<RetT>(std::forward<StlFn>(stl)(std::forward<Args>(args)...));

        //TODO add support for if count < N but > a smaller vector size

        {
        std::size_t i = 0;
        for(; i + N + src_count <= dest_count; i += N) {
            RetT ret = std::forward<LoopFn>(loop)(std::forward<Args>(args)..., dest_count, i);
            if(ret == fail_value) continue;
            return ret;
        }
        if (i + src_count >= dest_count) return fail_value;
        }


        return std::forward<LoopFn>(loop)(std::forward<Args>(args)..., dest_count, (dest_count - N - src_count));
    }
}
}


namespace zstring{ 
namespace impl {
    //Same as simd_fn but in reverse
    template<typename Arch, typename DataT, typename StlFn, typename LoopFn, typename RetT, typename... Args>
    constexpr RetT rsimd_fn(StlFn&& stl, LoopFn&& loop, std::size_t count, RetT fail_value, Args&&... args) noexcept {
        constexpr std::size_t N = Arch::template vector<DataT>::slots;
        if(count < N) return reinterpret_cast<RetT>(std::forward<StlFn>(stl)(std::forward<Args>(args)..., count));

        //TODO add support for if count < N but > a smaller vector size

        {
        std::size_t i = count;
        while(i >= N) {
            i -= N;
            RetT ret = std::forward<LoopFn>(loop)(std::forward<Args>(args)..., i, N);
            if(ret == fail_value) continue;
            return ret;
        }
        if (i == 0) return fail_value;
        }

        return std::forward<LoopFn>(loop)(std::forward<Args>(args)..., 0, N);
    }
}
}