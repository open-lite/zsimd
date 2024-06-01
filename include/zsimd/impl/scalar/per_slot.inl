#pragma once
#include "zsimd/impl/scalar.hpp"


namespace zsimd {
    template<typename T, typename Ret, typename... Args, typename Functor> ZSIMD_TARGET_SCALAR
    scalar::vector<T> scalar::per_slot(Functor&& func, Args&&... args) {
        vector<T> ret{};
        for(std::size_t i = 0; i < vector<T>::slots; i++)
            ret.native()[i] = static_cast<T>(std::forward<Functor>(func)(extract<Args>::value(std::forward<Args>(args), i)...));
        return ret;
    }
}