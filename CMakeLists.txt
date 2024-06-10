cmake_minimum_required(VERSION 3.23)

### zsimd ###
project(zsimd VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)


add_library(${PROJECT_NAME} INTERFACE)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER 
    "include/${PROJECT_NAME}.hpp"
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

list(TRANSFORM ${PROJECT_NAME}_HEADER_FILES PREPEND "include/${PROJECT_NAME}/")
target_sources(${PROJECT_NAME} PUBLIC FILE_SET ${PROJECT_NAME}_HEADERS TYPE HEADERS BASE_DIRS "include" FILES ${${PROJECT_NAME}_HEADER_FILES})

## zstring ##
set(ZSTRING_NAME zstring)


add_library(${ZSTRING_NAME} INTERFACE)
set_target_properties(${ZSTRING_NAME} PROPERTIES PUBLIC_HEADER 
    "include/${ZSTRING_NAME}.hpp"
)
set(${ZSTRING_NAME}_HEADER_FILES
    "manip/strcpy.hpp"
    "manip/strncpy.hpp"
    "manip/strcat.hpp"
    "manip/strncat.hpp"
    "manip/strxfrm.hpp"

    "exam/strlen.hpp"
    "exam/strcmp.hpp"
    "exam/strncmp.hpp"
    "exam/strcoll.hpp"
    "exam/strchr.hpp"
    "exam/strrchr.hpp"
    "exam/strspn.hpp"
    "exam/strcspn.hpp"
    "exam/strpbrk.hpp"
    "exam/strstr.hpp"
    "exam/strtok.hpp"

    "mem/memchr.hpp"
    "mem/memrchr.hpp"
    "mem/memcmp.hpp"
    "mem/memset.hpp"
    "mem/memcpy.hpp"
    "mem/memmove.hpp"

    "mem/mem_fn.hpp"
)

list(TRANSFORM ${ZSTRING_NAME}_HEADER_FILES PREPEND "include/${ZSTRING_NAME}/")
target_sources(${ZSTRING_NAME} PUBLIC FILE_SET ${ZSTRING_NAME}_HEADERS TYPE HEADERS BASE_DIRS "include" FILES ${${ZSTRING_NAME}_HEADER_FILES})


### include directory ###
cmake_path(SET SELF_INC_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(TO_NATIVE_PATH "${SELF_INC_CMAKE_DIR}" SELF_INC_DIR)
target_include_directories(${PROJECT_NAME} SYSTEM BEFORE INTERFACE "${SELF_INC_DIR}")
message(STATUS "Including self directory: ${SELF_INC_DIR}")


install(TARGETS ${PROJECT_NAME} FILE_SET ${PROJECT_NAME}_HEADERS)
install(TARGETS ${ZSTRING_NAME} FILE_SET ${ZSTRING_NAME}_HEADERS)