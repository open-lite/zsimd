cmake_minimum_required(VERSION 3.23)

project(zsimd VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)


add_library(${PROJECT_NAME} INTERFACE)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER 
    "include/zsimd.hpp"
)
set(${PROJECT_NAME}_HEADER_FILES
    "duplicate_foreach.h"

    "attrib/current_arch.h"
    "attrib/expand.h"
    "attrib/flatten.h"
    "attrib/target_clones.h"
    "attrib/target.h"
    "attrib/align.h"

    "types/generic_vector.hpp"
    "types/type_traits.hpp"

    "arch/scalar.hpp"
    "arch/scalar/data_transfer.inl"
    "arch/scalar/arithmetic.inl"
    "arch/scalar/math.inl"
    "arch/scalar/comparison.inl"
    "arch/scalar/bitwise.inl"
    "arch/scalar/per_slot.inl"
    "arch/scalar/pure/arithmetic.inl"
    "arch/scalar/pure/arithmetic_impl.inl"
    "arch/scalar/pure/math.inl"
    "arch/scalar/pure/comparison.inl"
    "arch/scalar/pure/bitwise.inl"
    "arch/scalar/pure/bitwise_impl.inl"
)

list(TRANSFORM ${PROJECT_NAME}_HEADER_FILES PREPEND "include/zsimd/")
target_sources(${PROJECT_NAME} PUBLIC FILE_SET ${PROJECT_NAME}_HEADERS TYPE HEADERS BASE_DIRS "include" FILES ${${PROJECT_NAME}_HEADER_FILES})


### include directory ###
cmake_path(SET SELF_INC_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(TO_NATIVE_PATH "${SELF_INC_CMAKE_DIR}" SELF_INC_DIR)
target_include_directories(${PROJECT_NAME} SYSTEM BEFORE INTERFACE "${SELF_INC_DIR}")
message(STATUS "Including self directory: ${SELF_INC_DIR}")


install(TARGETS ${PROJECT_NAME} FILE_SET ${PROJECT_NAME}_HEADERS)