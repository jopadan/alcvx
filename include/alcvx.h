#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdalign.h>
#include <sys/param.h>
#include <stdarg.h>

#define PARENS ()
#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#undef countof
#define countof(x) sizeof(typeof((x)))/sizeof(typeof((x)[0])) 
#define cnt(x) countof(x)

#define BITOP_RUP01__(x) (             (x) | (             (x) >>  1))
#define BITOP_RUP02__(x) (BITOP_RUP01__(x) | (BITOP_RUP01__(x) >>  2))
#define BITOP_RUP04__(x) (BITOP_RUP02__(x) | (BITOP_RUP02__(x) >>  4))
#define BITOP_RUP08__(x) (BITOP_RUP04__(x) | (BITOP_RUP04__(x) >>  8))
#define BITOP_RUP16__(x) (BITOP_RUP08__(x) | (BITOP_RUP08__(x) >> 16))

#define BIT_CEIL(x) (BITOP_RUP16__(((uint32_t)(x)) - 1) + 1)

#if   defined(__clang__)
#define vec(T,N) typeof(T __attribute__((ext_vector_type(N))))
#elif defined(__GNUC__)
#define vec(T,N) typeof(T __attribute__((vector_size(sizeof(T) * BIT_CEIL(N)))))
#elif defined(_MSC_VER)
#define vec(T,N) typeof(T __declspec((align(sizeof(T)*BIT_CEIL(N))))[BIT_CEIL(N)])
#warn "Your compiler doens't support vector extensions."
#warn "Using aligned arrays without operators instead."
#else
#define vec(T,N) typeof(T __attribute__((aligned(sizeof(T)*BIT_CEIL(N))))[BIT_CEIL(N)])
#warn "Your compiler doens't support vector extensions."
#warn "Using aligned arrays without operators instead."
#endif

#define ALCVX(src,n) (*(vec(typeof(src[0]),n)*)src)

#define sum(a,n,i) \
({ \
typeof((a)[0]) dst = i; \
_Pragma("omp simd reduction(+:dst)") \
for(size_t j = 0; j < MIN(cnt(a),n); j++) \
	dst += (a)[j]; \
dst; \
})

#define dot(a,b,n,i) \
({ \
typeof((a)[0]) dst = i; \
_Pragma("omp simd reduction(+:dst)") \
for(size_t j = 0; j < MIN(MIN(cnt(a),cnt(b)),n); j++) \
	dst += (a)[j] * (b)[j]; \
dst; \
})

#define numargs(...) sizeof((int[]){__VA_ARGS__})/sizeof(int)
#define perm_first(a,i,...) (a)[i]

#define minor(x,y,t,n,...) \
({ \
vec(t,n) a[] = (vec(t,n)[]){__VA_ARGS__}; \
vec(t,n-1) dst[n-1]; \
for(size_t i = 0; i < n-1; i++) \
	for(size_t j = 0; j < n-1; j++) \
		dst[i][j] = (i <  x && j <  y) ? a[i  ][j  ] : \
		            (i >= x && j <  y) ? a[i+1][j  ] : \
		            (i <  x && j >= y) ? a[i  ][j+1] : \
		                                 a[i+1][j+1] ; \
dst; \
})

#define sum3(a) sum(a,3,0)
#define sum4(a) sum(a,4,0)
#define dot3(a,b) dot(a,b,3,0)
#define dot4(a,b) dot(a,b,4,0)
#define perm(a,...) { __VA_OPT__(EXPAND(perm_helper(a,__VA_ARGS__))) }
#define perm_helper(a,i,...) (a)[i], __VA_OPT__(perm_again PARENS (a,__VA_ARGS__))
#define perm_again() perm_helper

#define perm3(a,...) (vec(typeof((a)[0]),3))perm(a,__VA_ARGS__)
#define perm4(a,...) (vec(typeof((a)[0]),4))perm(a,__VA_ARGS__)

#define cross3(a,b) \
  perm3(a,1,2,0) * perm3(b,2,0,1) \
- perm3(a,2,1,0) * perm3(b,1,2,0)
/*
#define cross4(a,b,c) (vec(typeof((a)[0]),4))\
{ det(perm3(a,1,2,3), perm3(b,1,2,3), perm3(c,1,2,3)), \
 -det(perm3(a,0,2,3), perm3(b,0,2,3), perm3(c,0,2,3)), \
  det(perm3(a,0,1,3), perm3(b,0,1,3), perm3(c,0,1,3)), \
 -det(perm3(a,0,1,2), perm3(b,0,1,2), perm3(c,0,1,2)) }
*/

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
typedef vec_t          vec9_t[9];
typedef vec_t          vec10_t[10];
typedef vec_t          vec11_t[11];
typedef vec_t          vec12_t[12];
typedef vec_t          vec13_t[13];
typedef vec_t          vec14_t[14];
typedef vec_t          vec15_t[15];
typedef vec_t          vec16_t[16];

typedef vec(float,2)  avec2_t;
typedef vec(float,3)  avec3_t;
typedef vec(float,4)  avec4_t;
typedef vec(float,5)  avec5_t;
typedef vec(float,6)  avec6_t;
typedef vec(float,7)  avec7_t;
typedef vec(float,8)  avec8_t;
typedef vec(float,9)  avec9_t;
typedef vec(float,10) avec10_t;
typedef vec(float,11) avec11_t;
typedef vec(float,12) avec12_t;
typedef vec(float,13) avec13_t;
typedef vec(float,14) avec14_t;
typedef vec(float,15) avec15_t;
typedef vec(float,16) avec16_t;

