#pragma once
#include <stdint.h>
#include <stddef.h>
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

#define TO_VEC(src,n) (*(VEC(typeof(src[0]),n)*)src)
#define TO_POS(src,n) ( VEC(src,n) dst = TO_VEC(src,n); if(src[n-1] != 0) dst/=src[n-1]; dst; )
#define TO_DIR(a,b) ( VEC(typeof(a[0]),countof(a)) dst = ; if(src[n-1] != 0) dst/=src[nx-1]; dst; )
