#pragma once
#include <bitset>
#include <cstddef>
#include <climits>
#include <cstdint>
#include <type_traits>
#include <array>

#if __cpp_constexpr >= 201304L
#define __ZSIMD_VECTOR_CONSTEXPR constexpr
#else 
#define __ZSIMD_VECTOR_CONSTEXPR inline
#endif


namespace zsimd {
    template<typename T, typename ArchTy, 
        typename SingleFloatVecTy, typename DoubleFloatVecTy, 
        typename IntVecTy, typename UIntVecTy = IntVecTy>
    struct basic_vector {
        using value_type = T;

        using data_type = typename std::conditional<std::is_floating_point<T>::value, 
            typename std::conditional<sizeof(T) == 64/8,          DoubleFloatVecTy, SingleFloatVecTy>::type, 
            typename std::conditional<std::is_unsigned<T>::value, UIntVecTy,        IntVecTy        >::type
        >::type;
        using native_type = data_type;

        constexpr static std::size_t native_size = sizeof(native_type);
        constexpr static std::size_t slot_size  = sizeof(T);
        constexpr static std::size_t slots = native_size/slot_size;


        using array_type = std::array<T, slots>;
        using bitset_type = std::bitset<native_size * CHAR_BIT>;
        using mask_type = 
            typename std::conditional<slots <= 1,  bool, 
            typename std::conditional<slots <= 8,  std::uint8_t, 
            typename std::conditional<slots <= 16, std::uint16_t, 
            typename std::conditional<slots <= 32, std::uint32_t, std::uint64_t
        >::type>::type>::type>::type;



        //Aggregate member
        native_type _data;

        __ZSIMD_VECTOR_CONSTEXPR native_type&       native()       noexcept { return _data; }
        constexpr                native_type const& native() const noexcept { return _data; }
        constexpr explicit inline operator typename std::decay<native_type>::type() const noexcept { return _data; }


 
        //Conversion
        template<typename U>
        explicit __ZSIMD_VECTOR_CONSTEXPR operator basic_vector<U, ArchTy, SingleFloatVecTy, DoubleFloatVecTy, IntVecTy, UIntVecTy>() noexcept { 
            return ArchTy::template type_cast<basic_vector<U, ArchTy, SingleFloatVecTy, DoubleFloatVecTy, IntVecTy, UIntVecTy>>(*this);
        }


        //Data Transfer/Store
        explicit __ZSIMD_VECTOR_CONSTEXPR operator array_type()  const noexcept { return ArchTy::to_array(*this); }
        explicit __ZSIMD_VECTOR_CONSTEXPR operator bitset_type() const noexcept { return ArchTy::to_bits (*this); }
        explicit __ZSIMD_VECTOR_CONSTEXPR operator mask_type()   const noexcept { return ArchTy::to_mask (*this); }



        //Assignment
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator += (const basic_vector& v) noexcept { *this = ArchTy::add(*this, v); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator -= (const basic_vector& v) noexcept { *this = ArchTy::sub(*this, v); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator *= (const basic_vector& v) noexcept { *this = ArchTy::mul(*this, v); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator /= (const basic_vector& v) noexcept { *this = ArchTy::div(*this, v); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator %= (const basic_vector& v) noexcept { *this = ArchTy::mod(*this, v); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator &= (const basic_vector& v) noexcept { *this = ArchTy::bitwise_and(*this, v); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator |= (const basic_vector& v) noexcept { *this = ArchTy::bitwise_or (*this, v); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator ^= (const basic_vector& v) noexcept { *this = ArchTy::bitwise_xor(*this, v); return *this; }

        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator <<=(int shift) noexcept { *this = ArchTy::bit_shiftl(*this, shift); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator >>=(int shift) noexcept { *this = ArchTy::bit_shiftr(*this, shift); return *this; }


        //Increment/Decrement
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator++() noexcept { *this = ArchTy::incr(*this); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector& operator--() noexcept { *this = ArchTy::decr(*this); return *this; }

        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator++(int) noexcept { basic_vector old = *this; operator++(); return old; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator--(int) noexcept { basic_vector old = *this; operator--(); return old; }


        //Arithmetic
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator+ () noexcept { *this = ArchTy::positive   (*this); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator- () noexcept { *this = ArchTy::negative   (*this); return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator~ () noexcept { *this = ArchTy::bitwise_not(*this); return *this; } 

        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator+ (const basic_vector& v) noexcept { *this += v; return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator- (const basic_vector& v) noexcept { *this -= v; return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator* (const basic_vector& v) noexcept { *this *= v; return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator/ (const basic_vector& v) noexcept { *this /= v; return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator% (const basic_vector& v) noexcept { *this &= v; return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator& (const basic_vector& v) noexcept { *this &= v; return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator| (const basic_vector& v) noexcept { *this |= v; return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator^ (const basic_vector& v) noexcept { *this ^= v; return *this; }

        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator<<(int shift) noexcept { *this <<= shift; return *this; }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator>>(int shift) noexcept { *this >>= shift; return *this; }


        //Logical
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator! ()                      noexcept { return ArchTy::logical_not(*this);    }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator||(const basic_vector& v) noexcept { return ArchTy::logical_or (*this, v); }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator&&(const basic_vector& v) noexcept { return ArchTy::logical_and(*this, v); }


        //Comparison
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator==(const basic_vector& v) noexcept { return ArchTy::eq (*this, v); }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator!=(const basic_vector& v) noexcept { return ArchTy::neq(*this, v); }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator< (const basic_vector& v) noexcept { return ArchTy::lt (*this, v); }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator> (const basic_vector& v) noexcept { return ArchTy::gt (*this, v); }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator<=(const basic_vector& v) noexcept { return ArchTy::leq(*this, v); }
        __ZSIMD_VECTOR_CONSTEXPR basic_vector operator>=(const basic_vector& v) noexcept { return ArchTy::geq(*this, v); }
    };
}