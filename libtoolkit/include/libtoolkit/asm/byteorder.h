#ifndef _LIBTOOLKIT_ASM_BYTEORDER_H
#define _LIBTOOLKIT_ASM_BYTEORDER_H

#ifndef _LIBTOOLKIT_BYTEORDER_H
#error "only <include/byteorder.h> can be included directly"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * An internal function to swap bytes in a 16-bit value.
 *
 * It is used by bswap16() when the value is constant. Do not use
 * this function directly; bswap16() is preferred.
 */
static inline uint16_t
constant_bswap16(uint16_t x)
{
	return (uint16_t)(((x & 0x00ffU) << 8) |
		((x & 0xff00U) >> 8));
}

/*
 * An internal function to swap bytes in a 32-bit value.
 *
 * It is used by bswap32() when the value is constant. Do not use
 * this function directly; bswap32() is preferred.
 */
static inline uint32_t
constant_bswap32(uint32_t x)
{
	return  ((x & 0x000000ffUL) << 24) |
		((x & 0x0000ff00UL) << 8) |
		((x & 0x00ff0000UL) >> 8) |
		((x & 0xff000000UL) >> 24);
}

/*
 * An internal function to swap bytes of a 64-bit value.
 *
 * It is used by bswap64() when the value is constant. Do not use
 * this function directly; bswap64() is preferred.
 */
static inline uint64_t
constant_bswap64(uint64_t x)
{
	return  ((x & 0x00000000000000ffULL) << 56) |
		((x & 0x000000000000ff00ULL) << 40) |
		((x & 0x0000000000ff0000ULL) << 24) |
		((x & 0x00000000ff000000ULL) <<  8) |
		((x & 0x000000ff00000000ULL) >>  8) |
		((x & 0x0000ff0000000000ULL) >> 24) |
		((x & 0x00ff000000000000ULL) >> 40) |
		((x & 0xff00000000000000ULL) >> 56);
}

/*
 * An architecture-optimized byte swap for a 16-bit value.
 *
 * Do not use this function directly. The preferred function is bswap16().
 */
static inline uint16_t arch_bswap16(uint16_t _x)
{
	register uint16_t x = _x;
	asm volatile ("xchgb %b[x1],%h[x2]"
		      : [x1] "=Q" (x)
		      : [x2] "0" (x)
		      );
	return x;
}

/*
 * An architecture-optimized byte swap for a 32-bit value.
 *
 * Do not use this function directly. The preferred function is bswap32().
 */
static inline uint32_t arch_bswap32(uint32_t _x)
{
	register uint32_t x = _x;
	asm volatile ("bswap %[x]"
		      : [x] "+r" (x)
		      );
	return x;
}

/*
 * An architecture-optimized byte swap for a 64-bit value.
 *
 * Do not use this function directly. The preferred function is bswap64().
 */
#ifdef __x86_64__
/* 64-bit mode */
static inline uint64_t arch_bswap64(uint64_t _x)
{
	register uint64_t x = _x;
	asm volatile ("bswap %[x]"
		      : [x] "+r" (x)
		      );
	return x;
}
#else /* ! __x86_64__ */
/* Compat./Leg. mode */
static inline uint64_t arch_bswap64(uint64_t x)
{
	uint64_t ret = 0;
	ret |= ((uint64_t)arch_bswap32(x & 0xffffffffUL) << 32);
	ret |= ((uint64_t)arch_bswap32((x >> 32) & 0xffffffffUL));
	return ret;
}
#endif /* __x86_64__ */

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_ASM_BYTEORDER_H */
