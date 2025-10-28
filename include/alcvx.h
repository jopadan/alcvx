#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdalign.h>

#undef countof
#define countof(x) (sizeof(x) / sizeof(x[0]))

#define BITOP_RUP01__(x) (             (x) | (             (x) >>  1))
#define BITOP_RUP02__(x) (BITOP_RUP01__(x) | (BITOP_RUP01__(x) >>  2))
#define BITOP_RUP04__(x) (BITOP_RUP02__(x) | (BITOP_RUP02__(x) >>  4))
#define BITOP_RUP08__(x) (BITOP_RUP04__(x) | (BITOP_RUP04__(x) >>  8))
#define BITOP_RUP16__(x) (BITOP_RUP08__(x) | (BITOP_RUP08__(x) >> 16))

#define BIT_CEIL(x) (BITOP_RUP16__(((uint32_t)(x)) - 1) + 1)

#if   defined(__clang__)
#define VEC(T,N) T __attribute__((ext_vector_type(N)))
#elif defined(__GNUC__)
#define VEC(T,N) T __attribute__((vector_size(sizeof(T) * BIT_CEIL(N))))
#elif defined(_MSC_VER)
#define VEC(T,N) typeof(T __declspec((align(sizeof(T)*BIT_CEIL(N))))[BIT_CEIL(N)])
#warn "Your compiler doens't support vector extensions."
#warn "Using aligned arrays without operators instead."
#else
#define VEC(T,N) typeof(T __attribute__((aligned(sizeof(T)*BIT_CEIL(N))))[BIT_CEIL(N)])
#warn "Your compiler doens't support vector extensions."
#warn "Using aligned arrays without operators instead."
#endif

#define ALCVX(src,n) (*(VEC(typeof(src[0]),n)*)src)


/* standard scalar types */
typedef float    f32;
typedef double   f64;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef  int64_t i64;
typedef  int32_t i32;
typedef  int16_t i16;
typedef  int8_t  i8;

typedef  int64_t s64;
typedef  int32_t s32;
typedef  int16_t s16;
typedef  int8_t  s8;

typedef  char     c8;
typedef  bool     b8;
typedef enum be32 : u32
{
	ALCVX_TRUE  = (const u32) true,
	ALCVX_FALSE = (const u32)!true,
} be32;

typedef  uintptr_t uptr;
typedef   intptr_t iptr;
typedef     size_t usz;
typedef    ssize_t ssz;

/* quake vector types */
typedef float          vec_t;
typedef vec_t          vec2_t[2];
typedef vec_t          vec3_t[3];
typedef vec_t          vec4_t[4];
typedef vec_t          vec5_t[5];
typedef vec_t          vec6_t[6];
typedef vec_t          vec7_t[7];
typedef vec_t          vec8_t[8];

typedef VEC(float,2)  avec2_t;
typedef VEC(float,3)  avec3_t;
typedef VEC(float,4)  avec4_t;
typedef VEC(float,5)  avec5_t;
typedef VEC(float,6)  avec6_t;
typedef VEC(float,7)  avec7_t;
typedef VEC(float,8)  avec8_t;
