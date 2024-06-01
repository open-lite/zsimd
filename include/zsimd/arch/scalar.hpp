#pragma once
#include <cstdint>
#include <cstddef>
#include <climits>
#include <type_traits>
#include "zsimd/types/type_traits.hpp"
#include "zsimd/types/basic_vector.hpp"

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
    private:
        constexpr static std::size_t native_bits = 64;

        template<typename T>
        using native_type = T[(native_bits/CHAR_BIT)/sizeof(T)];

    public:
        template<typename T>
        using vector = basic_vector<T, scalar, native_type<T>, native_type<T>, native_type<T>>;
        //template<typename T>
        //using vector_bool = vector<T, true>; 

        template<typename T>
        using mask = typename vector<T>::mask_type;
        //alignas on type alias is a GCC-only extension; clang does not support it.
        template<typename T>
        using array  /*alignas(vector<T>::data_size)*/ = typename vector<T>::array_type;
        template<typename T>
        using bitset /*alignas(vector<T>::data_size)*/ = typename vector<T>::bitset_type;
        
        static_assert(std::is_same<typename array<int>::pointer, typename std::decay<native_type<int>>::type>::value && sizeof(array<int>) == native_bits/CHAR_BIT);


    public:
        /* Data transfer */
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> loadu(T const* const data) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> ploadu(T const* const data, std::size_t remaining_len) noexcept; //iloadu
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> loada(T const* const data) noexcept;

        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> broadcast(T val) noexcept;

        template<typename T> ZSIMD_TARGET_SCALAR static
        vector<T> all_zeros() noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> all_ones() noexcept;
        

        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        array<T> store(vector<T> v) noexcept;


        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        array<T> to_array(vector<T> v) noexcept;

        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        mask<T> to_mask(vector<T> v) noexcept;

        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        bitset<T> to_bitset(vector<T> v) noexcept;

        
        template<typename To, typename From> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<To> type_cast(vector<From> v) noexcept;

        template<typename To, typename From, enable_if_2<To, From, traits::same_size> = true> ZSIMD_TARGET_SCALAR_CPP20 static
        vector<To> bit_cast (vector<From> v) noexcept;
        
        //template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        //vector<cond<T>> bool_cast(vector<T> v) noexcept;


        template<typename T> ZSIMD_TARGET_SCALAR static
        mask<T> left_mask(std::size_t idx) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR static
        mask<T> right_mask(std::size_t idx) noexcept;


        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> slot_shiftl(vector<T> v, std::size_t n_slots) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> slot_shiftr(vector<T> v, std::size_t n_slots) noexcept;



        /* Arithmetic */
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> add(vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> sub(vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> mul(vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> div(vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> mod(vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> rem(vector<T> a, vector<T> b) noexcept;
        
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> positive(vector<T> v) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> negative(vector<T> v) noexcept;

        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> reciprocal(vector<T> v) noexcept;

        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> decr(vector<T> v) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> incr(vector<T> v) noexcept;

        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> min(vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> max(vector<T> a, vector<T> b) noexcept;


        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> add_s(vector<T> a, vector<T> b) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> sub_s(vector<T> a, vector<T> b) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> mul_s(vector<T> a, vector<T> b) noexcept;


        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> fma(vector<T> a, vector<T> b, vector<T> c) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> fms(vector<T> a, vector<T> b, vector<T> c) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> fnma(vector<T> a, vector<T> b, vector<T> c) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> fnms(vector<T> a, vector<T> b, vector<T> c) noexcept;


        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> logical_and(vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> logical_or (vector<T> a, vector<T> b) noexcept;
        
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> logical_not(vector<T> v) noexcept;



        /* Mathematical */
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> abs(vector<T> v) noexcept;


        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> expe (vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> exp2 (vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> exp10(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> expem1(vector<T> v) noexcept;

        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> ln(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> log2(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> log10(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> ln1p(vector<T> v) noexcept;


        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> pow(vector<T> base, vector<T> exp) noexcept;
        
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> rsqrt(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> sqrt(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> cbrt(vector<T> v) noexcept;

        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> hypot(vector<T> a, vector<T> b) noexcept;


        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> sin(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> cos(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> tan(vector<T> v) noexcept;

        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> arcsin(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> arccos(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> arctan(vector<T> v) noexcept;

        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> sinh(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> cosh(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> tanh(vector<T> v) noexcept;

        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> arcsinh(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> arccosh(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> arctanh(vector<T> v) noexcept;


        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> half_to_even(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> half_to_inf(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> floor(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> ceil(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::floating> = true> ZSIMD_TARGET_SCALAR_MATH static
        vector<T> truncate(vector<T> v) noexcept;



        /* Comparison */
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> eq (vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> neq(vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> gt (vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> lt (vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> geq(vector<T> a, vector<T> b) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> leq(vector<T> a, vector<T> b) noexcept;


        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> is_even(vector<T> v) noexcept;
        template<typename T> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> is_odd (vector<T> v) noexcept;



        /* Bitwise manipulation */
        //template<typename To, typename From, enable_if_2<To, From, traits::same_size> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        //vector<To> bit_cast (vector<From> v) noexcept;


        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> bit_shiftl(vector<T> v, int shift) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> bit_shiftr(vector<T> v, int shift) noexcept;

        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> bit_shiftr_a(vector<T> v, int shift) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> bit_shiftr_l(vector<T> v, int shift) noexcept;
        

        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> bitwise_not(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> bitwise_and(vector<T> a, vector<T> b) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> bitwise_or (vector<T> a, vector<T> b) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> bitwise_xor(vector<T> a, vector<T> b) noexcept;


        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> is_ones (vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> is_zeros(vector<T> v) noexcept;

        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        bool is_all_ones (vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        bool is_all_zeros(vector<T> v) noexcept;


        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> rotr(vector<T> v, int shift) noexcept;
        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> rotl(vector<T> v, int shift) noexcept;


        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> countl_zero(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> countr_zero(vector<T> v) noexcept;

        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> countl_one(vector<T> v) noexcept;
        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> countr_one(vector<T> v) noexcept;

        template<typename T, enable_if<T, traits::unsigned_num, traits::integral> = true> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> popcount(vector<T> v) noexcept;



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
            ZSIMD_TARGET_SCALAR static type value(T&& v, std::size_t i) noexcept { return std::forward<T>(v).native()[i]; }
        };

        //Compiler *should* inline whatever function is being passed.
        template<typename T, typename Ret = T, typename... Args, typename Functor = Ret(typename extract<Args>::type...)> ZSIMD_TARGET_SCALAR_CPP14 static
        vector<T> per_slot(Functor&& func, Args&&... args);
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