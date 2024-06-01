#pragma once
#include <type_traits>
#include <cstddef>
#include <stdfloat>


//std::conjunction C++11 "backport"
namespace zsimd {
    template<typename...> struct conjunction     : std::true_type {};
    template<typename B0> struct conjunction<B0> : B0 {};

    template<typename B0, typename... Bn>
    struct conjunction<B0, Bn...> : std::conditional<static_cast<bool>(B0::value), conjunction<Bn...>, B0>::type {};


    template<typename...> struct disjunction : std::false_type {};
    template<typename B0> struct disjunction<B0> : B0 {};
    
    template<typename B0, typename... Bn>
    struct disjunction<B0, Bn...> : std::conditional<static_cast<bool>(B0::value), B0, disjunction<Bn...>>::type  {};
}

//enable_if shorthand used on SIMD functions
namespace zsimd {
    template<typename T, template<typename> typename... Args>
    using enable_if = typename std::enable_if<zsimd::conjunction<Args<T>...>::value, bool>::type;

    template<typename T, typename U, template<typename, typename> typename... Args>
    using enable_if_2 = typename std::enable_if<zsimd::conjunction<Args<T, U>...>::value, bool>::type;
}


//size of data type traits
namespace zsimd {
namespace traits {
    namespace impl {
        template<typename T, std::size_t N>
        using size = std::integral_constant<bool, sizeof(T) == N/8>;
    }

    template<typename T>
    using size_8  = impl::size<T, 8>;
    template<typename T>
    using size_16 = impl::size<T, 16>;
    template<typename T>
    using size_32 = impl::size<T, 32>;
    template<typename T>
    using size_64 = impl::size<T, 64>;

    template<typename A, typename B>
    using same_size = std::integral_constant<bool, sizeof(A) == sizeof(B)>;
}
}

//floating or signed/unsigned integral type traits
namespace zsimd {
namespace traits {
    template<typename T>
    using floating = std::is_floating_point<T>;

    template<typename T>
    using integral = std::is_integral<T>;

    template<typename T>
    using numeric = std::is_scalar<T>;
    template<typename T>
    using arithmetic = std::is_arithmetic<T>;

    template<typename T>
    using signed_num   = std::is_signed<T>;
    template<typename T>
    using unsigned_num = std::is_unsigned<T>;
}
}