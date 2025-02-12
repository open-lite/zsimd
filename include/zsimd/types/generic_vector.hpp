#pragma once
#include <bitset>
#include <cstddef>
#include <climits>
#include <cstdint>
#include <type_traits>
#include <array>


namespace zsimd {
    template<typename T, std::size_t B, typename ArchTy, 
        typename SingleFloatVecTy, typename DoubleFloatVecTy, 
        typename IntVecTy, typename UIntVecTy = IntVecTy>
    struct generic_vector {
        using native_type = typename std::conditional<std::is_floating_point<T>::value, 
            typename std::conditional<sizeof(T) >= 64 / CHAR_BIT, DoubleFloatVecTy, SingleFloatVecTy>::type, 
            typename std::conditional<std::is_signed<T>::value,   IntVecTy,         UIntVecTy       >::type
        >::type;

        constexpr static std::size_t native_size = sizeof(native_type);
        constexpr static std::size_t data_size   = B / CHAR_BIT;
        constexpr static std::size_t total_size  = data_size;

        constexpr static std::size_t block_size = native_size;
        constexpr static std::size_t blocks     = data_size / block_size;

        constexpr static std::size_t slot_size = sizeof(T);
        constexpr static std::size_t slots     = data_size / slot_size;

        using data_type = native_type[blocks];

        using value_type = T;
        using array_type = std::array<T, slots>;
        using bitset_type = std::bitset<data_size * CHAR_BIT>;
        using mask_type = 
            typename std::conditional<slots <= 1,  bool, 
            typename std::conditional<slots <= 8,  std::uint8_t, 
            typename std::conditional<slots <= 16, std::uint16_t, 
            typename std::conditional<slots <= 32, std::uint32_t, std::uint64_t
        >::type>::type>::type>::type;

        static_assert(B % (native_size * CHAR_BIT) == 0 || B <= (native_size * CHAR_BIT), "");
        static_assert(sizeof(data_type) == total_size);



        //Aggregate member
        data_type _data;

        constexpr data_type&       data()       noexcept { return _data; }
        constexpr                data_type const& data() const noexcept { return _data; }
        constexpr explicit inline operator typename std::decay<data_type>::type() const noexcept { return _data; }


 
        //Conversion
        template<typename U>
        explicit constexpr operator generic_vector<U, B, ArchTy, SingleFloatVecTy, DoubleFloatVecTy, IntVecTy, UIntVecTy>() noexcept { 
            return ArchTy::template type_cast<generic_vector<U, B, ArchTy, SingleFloatVecTy, DoubleFloatVecTy, IntVecTy, UIntVecTy>>(*this);
        }


        //Data Transfer/Store
        explicit constexpr operator array_type()  const noexcept { return ArchTy::to_array(*this); }
        explicit constexpr operator bitset_type() const noexcept { return ArchTy::to_bits (*this); }
        explicit constexpr operator mask_type()   const noexcept { return ArchTy::to_mask (*this); }



        //Assignment
        constexpr generic_vector& operator += (const generic_vector& v) noexcept { *this = ArchTy::add(*this, v); return *this; }
        constexpr generic_vector& operator -= (const generic_vector& v) noexcept { *this = ArchTy::sub(*this, v); return *this; }
        constexpr generic_vector& operator *= (const generic_vector& v) noexcept { *this = ArchTy::mul(*this, v); return *this; }
        constexpr generic_vector& operator /= (const generic_vector& v) noexcept { *this = ArchTy::div(*this, v); return *this; }
        constexpr generic_vector& operator %= (const generic_vector& v) noexcept { *this = ArchTy::mod(*this, v); return *this; }
        constexpr generic_vector& operator &= (const generic_vector& v) noexcept { *this = ArchTy::bitwise_and(*this, v); return *this; }
        constexpr generic_vector& operator |= (const generic_vector& v) noexcept { *this = ArchTy::bitwise_or (*this, v); return *this; }
        constexpr generic_vector& operator ^= (const generic_vector& v) noexcept { *this = ArchTy::bitwise_xor(*this, v); return *this; }

        constexpr generic_vector& operator <<=(int shift) noexcept { *this = ArchTy::bit_shiftl(*this, shift); return *this; }
        constexpr generic_vector& operator >>=(int shift) noexcept { *this = ArchTy::bit_shiftr(*this, shift); return *this; }


        //Increment/Decrement
        constexpr generic_vector& operator++() noexcept { *this = ArchTy::incr(*this); return *this; }
        constexpr generic_vector& operator--() noexcept { *this = ArchTy::decr(*this); return *this; }

        constexpr generic_vector operator++(int) noexcept { generic_vector old = *this; operator++(); return old; }
        constexpr generic_vector operator--(int) noexcept { generic_vector old = *this; operator--(); return old; }


        //Arithmetic
        constexpr generic_vector operator+ () noexcept { *this = ArchTy::positive   (*this); return *this; }
        constexpr generic_vector operator- () noexcept { *this = ArchTy::negative   (*this); return *this; }
        constexpr generic_vector operator~ () noexcept { *this = ArchTy::bitwise_not(*this); return *this; } 

        constexpr generic_vector operator+ (const generic_vector& v) noexcept { *this += v; return *this; }
        constexpr generic_vector operator- (const generic_vector& v) noexcept { *this -= v; return *this; }
        constexpr generic_vector operator* (const generic_vector& v) noexcept { *this *= v; return *this; }
        constexpr generic_vector operator/ (const generic_vector& v) noexcept { *this /= v; return *this; }
        constexpr generic_vector operator% (const generic_vector& v) noexcept { *this &= v; return *this; }
        constexpr generic_vector operator& (const generic_vector& v) noexcept { *this &= v; return *this; }
        constexpr generic_vector operator| (const generic_vector& v) noexcept { *this |= v; return *this; }
        constexpr generic_vector operator^ (const generic_vector& v) noexcept { *this ^= v; return *this; }

        constexpr generic_vector operator<<(int shift) noexcept { *this <<= shift; return *this; }
        constexpr generic_vector operator>>(int shift) noexcept { *this >>= shift; return *this; }


        //Logical
        constexpr generic_vector operator! ()                      noexcept { return ArchTy::logical_not(*this);    }
        constexpr generic_vector operator||(const generic_vector& v) noexcept { return ArchTy::logical_or (*this, v); }
        constexpr generic_vector operator&&(const generic_vector& v) noexcept { return ArchTy::logical_and(*this, v); }


        //Comparison
        constexpr generic_vector operator==(const generic_vector& v) noexcept { return ArchTy::eq (*this, v); }
        constexpr generic_vector operator!=(const generic_vector& v) noexcept { return ArchTy::neq(*this, v); }
        constexpr generic_vector operator< (const generic_vector& v) noexcept { return ArchTy::lt (*this, v); }
        constexpr generic_vector operator> (const generic_vector& v) noexcept { return ArchTy::gt (*this, v); }
        constexpr generic_vector operator<=(const generic_vector& v) noexcept { return ArchTy::leq(*this, v); }
        constexpr generic_vector operator>=(const generic_vector& v) noexcept { return ArchTy::geq(*this, v); }
    };
}


#define __ZSIMD_PER_BLOCK_BEGIN for(std::size_t i = 0; i < generic_vector<T, B>::blocks; ++i) {
#define __ZSIMD_PER_BLOCK_END   }