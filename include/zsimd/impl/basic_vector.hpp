#pragma once
#include <bitset>
#include <type_traits>
#include <array>

namespace zsimd {
    template<typename T, typename ArchTy, 
        typename MaskTy, 
        typename SingleFloatVecTy, typename DoubleFloatVecTy, 
        typename IntVecTy, typename UIntVecTy = IntVecTy>
    struct basic_vector {
        using data_type = typename std::conditional<std::is_floating_point<T>::value, 
            typename std::conditional<sizeof(T) == 64/8,          DoubleFloatVecTy, SingleFloatVecTy>::type, 
            typename std::conditional<std::is_unsigned<T>::value, UIntVecTy,        IntVecTy        >::type
        >::type;
        using native_type = data_type;

        constexpr static std::size_t total_size = sizeof(native_type);
        constexpr static std::size_t lane_size  = sizeof(T);
        constexpr static std::size_t lanes = total_size/lane_size;


        using mask_type = MaskTy;
        using array_type = std::array<T, lanes>;
        using bitset_type = std::bitset<total_size * 8>;


        //Aggregate member
        native_type _data;

        native_type&       native()       noexcept;
        native_type const& native() const noexcept;
        explicit inline operator native_type() const noexcept;


 
        //Conversion
        template<typename U>
        explicit inline operator basic_vector<U, ArchTy, MaskTy, SingleFloatVecTy, DoubleFloatVecTy, IntVecTy, UIntVecTy>() noexcept; 


        //Data Transfer/Store
        explicit inline operator array_type()  const noexcept;
        explicit inline operator bitset_type() const noexcept;
        explicit inline operator mask_type()   const noexcept;



        //Assignment
        inline basic_vector& operator += (const basic_vector& v) noexcept;
        inline basic_vector& operator -= (const basic_vector& v) noexcept;
        inline basic_vector& operator *= (const basic_vector& v) noexcept;
        inline basic_vector& operator /= (const basic_vector& v) noexcept;
        inline basic_vector& operator %= (const basic_vector& v) noexcept;
        inline basic_vector& operator &= (const basic_vector& v) noexcept;
        inline basic_vector& operator |= (const basic_vector& v) noexcept;
        inline basic_vector& operator ^= (const basic_vector& v) noexcept;
        inline basic_vector& operator <<=(const basic_vector& v) noexcept;
        inline basic_vector& operator >>=(const basic_vector& v) noexcept;


        //Increment/Decrement
        inline basic_vector& operator++()    noexcept;
        inline basic_vector& operator--()    noexcept;
        inline basic_vector  operator++(int) noexcept;
        inline basic_vector  operator--(int) noexcept;


        //Arithmetic
        inline basic_vector operator+ ()                     const noexcept;
        inline basic_vector operator- ()                     const noexcept;
        inline basic_vector operator+ (const basic_vector& v) const noexcept;
        inline basic_vector operator- (const basic_vector& v) const noexcept;
        inline basic_vector operator* (const basic_vector& v) const noexcept;
        inline basic_vector operator/ (const basic_vector& v) const noexcept;
        inline basic_vector operator% (const basic_vector& v) const noexcept;
        inline basic_vector operator~ ()                     const noexcept; 
        inline basic_vector operator& (const basic_vector& v) const noexcept;
        inline basic_vector operator| (const basic_vector& v) const noexcept;
        inline basic_vector operator^ (const basic_vector& v) const noexcept;

        inline basic_vector operator<<(int shift)            const noexcept;
        inline basic_vector operator>>(int shift)            const noexcept;


        //Logical
        //inline bool operator! ()                     const noexcept;
        //inline bool operator&&(const basic_vector& v) const noexcept;
        //inline bool operator||(const basic_vector& v) const noexcept;


        //Comparison
        inline basic_vector operator==(const basic_vector& v) const noexcept;
        inline basic_vector operator!=(const basic_vector& v) const noexcept;
        inline basic_vector operator< (const basic_vector& v) const noexcept;
        inline basic_vector operator> (const basic_vector& v) const noexcept;
        inline basic_vector operator<=(const basic_vector& v) const noexcept;
        inline basic_vector operator>=(const basic_vector& v) const noexcept;
    };
}