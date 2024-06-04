#pragma once
#include "zsimd/arch/scalar.hpp"


namespace zsimd {
    template<typename T, std::size_t B, typename Ret, typename... Args, typename Functor> ZSIMD_TARGET_SCALAR
    scalar::basic_vector<T, B> scalar::per_slot(Functor&& func, Args&&... args) {
        basic_vector<T, B> ret{};
        for(std::size_t i = 0; i < basic_vector<T, B>::slots; i++)
            ret.data()[i] = static_cast<T>(std::forward<Functor>(func)(extract<Args>::value(std::forward<Args>(args), i)...));
        return ret;
    }
}