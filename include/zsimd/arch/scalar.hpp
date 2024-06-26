#pragma once
#include <cstdint>
#include <cstddef>
#include <climits>
#include <type_traits>
#include "zsimd/types/type_traits.hpp"
#include "zsimd/types/generic_vector.hpp"

#if __cpp_constexpr >= 201304L
#define ZSIMD_TARGET_SCALAR_CPP14 constexpr 
#else 
#define ZSIMD_TARGET_SCALAR_CPP14 inline
#endif

#if __cpp_lib_bit_cast >= 201806L
#define ZSIMD_TARGET_SCALAR_CPP20 constexpr
#else
#define ZSIMD_TARGET_SCALAR_CPP20 inline
#endif

#if __cpp_constexpr >= 202207L
#define ZSIMD_TARGET_SCALAR_MATH constexpr
#else
#define ZSIMD_TARGET_SCALAR_MATH inline
#endif

#define ZSIMD_TARGET_SCALAR constexpr


namespace zsimd {
    struct scalar {
        template<typename T, std::size_t B>
        using basic_vector = generic_vector<T, B, scalar, T, T, T>;

        constexpr static std::size_t native_bits = 64;
        template<typename T>
        using vector = basic_vector<T, native_bits>;

        template<typename T>
        using vector128 = basic_vector<T, 128>;
        template<typename T>
        using vector256 = basic_vector<T, 256>;
        template<typename T>
        using vector512 = basic_vector<T, 512>;


        template<typename T, std::size_t B>
        using basic_mask = typename basic_vector<T, B>::mask_type;
        //alignas on type alias is a GCC-only extension; clang does not support it.
        template<typename T, std::size_t B>
        using basic_array  /*alignas(basic_vector<T, B>::data_size)*/ = typename basic_vector<T, B>::array_type;
        template<typename T, std::size_t B>
        using basic_bitset /*alignas(basic_vector<T, B>::data_size)*/ = typename basic_vector<T, B>::bitset_type;

        template<typename T>
        using mask   = basic_mask<T, native_bits>;
        template<typename T>
        using array  = basic_array<T, native_bits>;
        template<typename T>
        using bitset = basic_bitset<T, native_bits>;


    public:
        /* Data transfer */
        template<typename T, std::size_t B = native_bits> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> loadu(T const* const data) noexcept;
        template<typename T, std::size_t B = native_bits> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> ploadu(T const* const data, std::size_t remaining_len) noexcept; //iloadu
        template<typename T, std::size_t B = native_bits> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> loada(T const* const data) noexcept;

        template<typename T, std::size_t B = native_bits> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> broadcast(T val) noexcept;

        template<typename T, std::size_t B = native_bits> ZSIMD_TARGET_SCALAR static
        basic_vector<T, B> all_zeros() noexcept;
        template<typename T, std::size_t B = native_bits, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> all_ones() noexcept;
        

        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        T* const storeu(T* const dest, basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        T* const storea(T* const dest, basic_vector<T, B> v) noexcept;


        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_array<T, B> to_array(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_mask<T, B> to_mask(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_bitset<T, B> to_bitset(basic_vector<T, B> v) noexcept;

        
        template<typename To, typename From, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<To, B> type_cast(basic_vector<From, B> v) noexcept;

        template<typename To, typename From, std::size_t B, enable_if_2<To, From, traits::same_size> = true> ZSIMD_TARGET_SCALAR_CPP20 static
        basic_vector<To, B> bit_cast (basic_vector<From, B> v) noexcept;
        
        //template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        //vector<cond<T>> bool_cast(basic_vector<T, B> v) noexcept;


        template<bool Inclusive, typename T, std::size_t B = native_bits> ZSIMD_TARGET_SCALAR static
        basic_mask<T, B> left_mask(std::size_t idx) noexcept;
        template<bool Inclusive, typename T, std::size_t B = native_bits> ZSIMD_TARGET_SCALAR static
        basic_mask<T, B> right_mask(std::size_t idx) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> slot_shiftl(basic_vector<T, B> v, std::size_t n_slots) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> slot_shiftr(basic_vector<T, B> v, std::size_t n_slots) noexcept;



        /* Arithmetic */
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> add(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> sub(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> mul(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> div(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> mod(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> rem(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> positive(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> negative(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> reciprocal(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> decr(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> incr(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> min(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> max(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> add_s(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> sub_s(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> mul_s(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> fma(basic_vector<T, B> a, basic_vector<T, B> b, basic_vector<T, B> c) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> fms(basic_vector<T, B> a, basic_vector<T, B> b, basic_vector<T, B> c) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> fnma(basic_vector<T, B> a, basic_vector<T, B> b, basic_vector<T, B> c) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> fnms(basic_vector<T, B> a, basic_vector<T, B> b, basic_vector<T, B> c) noexcept;


        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> logical_and(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> logical_or (basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> logical_not(basic_vector<T, B> v) noexcept;



        /* Mathematical */
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> abs(basic_vector<T, B> v) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> expe (basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> exp2 (basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> exp10(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> expem1(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> ln(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> log2(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> log10(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> ln1p(basic_vector<T, B> v) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> pow(basic_vector<T, B> base, basic_vector<T, B> exp) noexcept;
        
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> rsqrt(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> sqrt(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> cbrt(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> hypot(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> sin(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> cos(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> tan(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> arcsin(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> arccos(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> arctan(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> sinh(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> cosh(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> tanh(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> arcsinh(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> arccosh(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> arctanh(basic_vector<T, B> v) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> half_to_even(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> half_to_inf(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> floor(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> ceil(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        basic_vector<T, B> truncate(basic_vector<T, B> v) noexcept;



        /* Comparison */
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> eq (basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> neq(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> gt (basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> lt (basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> geq(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> leq(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;


        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> is_even(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> is_odd (basic_vector<T, B> v) noexcept;



        /* Bitwise manipulation */
        //template<typename To, typename From, enable_if_2<To, From, traits::same_size> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        //vector<To> bit_cast (vector<From> v) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> bit_shiftl(basic_vector<T, B> v, int shift) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> bit_shiftr(basic_vector<T, B> v, int shift) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> bit_shiftr_a(basic_vector<T, B> v, int shift) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> bit_shiftr_l(basic_vector<T, B> v, int shift) noexcept;
        

        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> bitwise_not(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> bitwise_and(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> bitwise_or (basic_vector<T, B> a, basic_vector<T, B> b) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> bitwise_xor(basic_vector<T, B> a, basic_vector<T, B> b) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> is_ones (basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> is_zeros(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        bool is_all_ones (basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        bool is_all_zeros(basic_vector<T, B> v) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> rotr(basic_vector<T, B> v, int shift) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> rotl(basic_vector<T, B> v, int shift) noexcept;


        template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> countl_zero(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> countr_zero(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> countl_one(basic_vector<T, B> v) noexcept;
        template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> countr_one(basic_vector<T, B> v) noexcept;

        template<typename T, std::size_t B, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> popcount(basic_vector<T, B> v) noexcept;



    public:
        /* Pure Scalar Arithmetic */
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T add(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T sub(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T mul(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T div(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T mod(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        T mod(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T rem(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        T rem(T a, T b) noexcept;
        
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T positive(T val) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T negative(T val) noexcept;

        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T reciprocal(T val) noexcept;

        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T decr(T val) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T incr(T val) noexcept;

        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T min(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T max(T a, T b) noexcept;



        template<typename T, enable_if<T, traits::integral, traits::unsigned_num> = true> ZSIMD_TARGET_SCALAR static
        T add_s(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::integral, traits::signed_num> = true> ZSIMD_TARGET_SCALAR static
        T add_s(T a, T b) noexcept;

        template<typename T, enable_if<T, traits::integral, traits::unsigned_num> = true> ZSIMD_TARGET_SCALAR static
        T sub_s(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::integral, traits::signed_num> = true> ZSIMD_TARGET_SCALAR static
        T sub_s(T a, T b) noexcept;
        
        template<typename T, enable_if<T, traits::integral, traits::unsigned_num> = true> ZSIMD_TARGET_SCALAR static
        T mul_s(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::integral, traits::signed_num> = true> ZSIMD_TARGET_SCALAR static
        T mul_s(T a, T b) noexcept;


        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR static
        T fma(T a, T b, T c) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR static
        T fms(T a, T b, T c) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR static
        T fnma(T a, T b, T c) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR static
        T fnms(T a, T b, T c) noexcept;


        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool logical_and(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool logical_or (T a, T b) noexcept;
        
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool logical_not(T val) noexcept;



        /* Pure Scalar Mathematical */
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        T abs(T val) noexcept;


        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T expe (T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T exp2 (T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T exp10(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T expem1(T val) noexcept;

        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T ln(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T log2(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T log10(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T ln1p(T val) noexcept;


        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T pow(T base, T exp) noexcept;
        
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T rsqrt(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T sqrt(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T cbrt(T val) noexcept;

        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T hypot(T a, T b) noexcept;


        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T sin(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T cos(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T tan(T val) noexcept;

        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T arcsin(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T arccos(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T arctan(T val) noexcept;

        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T sinh(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T cosh(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T tanh(T val) noexcept;

        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T arcsinh(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T arccosh(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T arctanh(T val) noexcept;


        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T half_to_even(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T half_to_inf(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T floor(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T ceil(T val) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH
        T truncate(T val) noexcept;



        /* Pure Scalar Comparison */
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool eq (T a, T b) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool neq(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool gt (T a, T b) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool lt (T a, T b) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool geq(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool leq(T a, T b) noexcept;


        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool is_even(T val) noexcept;
        template<typename T, enable_if<T, traits::arithmetic> = true> ZSIMD_TARGET_SCALAR static
        bool is_odd (T val) noexcept;



        /* Pure Scalar Bitwise */
        //template<typename To, typename From, enable_if_2<To, From, traits::same_size> = true> ZSIMD_TARGET_SCALAR static
        //To bit_cast(From val) noexcept;


        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T bit_shiftl(T val, int shift) noexcept;
        template<typename T, enable_if<T, traits::integral, traits::unsigned_num> = true> ZSIMD_TARGET_SCALAR static
        T bit_shiftr(T val, int shift) noexcept;
        template<typename T, enable_if<T, traits::integral, traits::signed_num> = true> ZSIMD_TARGET_SCALAR static
        T bit_shiftr(T val, int shift) noexcept;

        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T bit_shiftr_a(T val, int shift) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T bit_shiftr_l(T val, int shift) noexcept;


        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T bitwise_not(T val) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T bitwise_and(T a, T b) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T bitwise_or (T a, T b) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T bitwise_xor(T a, T b) noexcept;


        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        bool is_ones (T val) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        bool is_zeros(T val) noexcept;


        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T rotr(T val, int shift) noexcept;
        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR static
        T rotl(T val, int shift) noexcept;


        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        std::uint8_t countl_zero(T val) noexcept;
        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        std::uint8_t countr_zero(T val) noexcept;

        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        std::uint8_t countl_one(T val) noexcept;
        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        std::uint8_t countr_one(T val) noexcept;

        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        std::uint8_t popcount(T val) noexcept;


    //Scalar-only helper functions that call a function 'func' on every vector slot
    private:
        template<typename T, typename = void>
        struct extract {
            using type = T;
            ZSIMD_TARGET_SCALAR static T value(T&& t, std::size_t i) noexcept { return std::forward<T>(t); }
        };

        template<typename T>
        struct extract<T, typename std::enable_if<!std::is_arithmetic<T>::value>::type> {
            using type = typename std::remove_reference<T>::type::value_type;
            ZSIMD_TARGET_SCALAR static type value(T&& v, std::size_t i) noexcept { return std::forward<T>(v).data()[i]; }
        };

        //Compiler *should* inline whatever function is being passed.
        template<typename T, std::size_t B, typename Ret = T, typename... Args, typename Functor = Ret(typename extract<Args>::type...)> ZSIMD_TARGET_SCALAR_CPP14 static
        basic_vector<T, B> per_slot(Functor&& func, Args&&... args);
    };
}

#include "zsimd/arch/scalar/data_transfer.inl"
#include "zsimd/arch/scalar/arithmetic.inl"
#include "zsimd/arch/scalar/math.inl"
#include "zsimd/arch/scalar/comparison.inl"
#include "zsimd/arch/scalar/bitwise.inl"

#include "zsimd/arch/scalar/pure/arithmetic.inl"
#include "zsimd/arch/scalar/pure/math.inl"
#include "zsimd/arch/scalar/pure/comparison.inl"
#include "zsimd/arch/scalar/pure/bitwise.inl"

#include "zsimd/arch/scalar/per_slot.inl"