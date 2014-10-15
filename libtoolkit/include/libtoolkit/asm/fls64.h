#ifndef _LIBTOOLKIT_ASM_FLS64_T
#define _LIBTOOLKIT_ASM_FLS64_T

#include <libtoolkit/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * fls64 - find last set bit in a 64-bit word
 * @x: the word to search
 *
 * This is defined in a similar way as the libc and compiler builtin
 * ffsll, but returns the position of the most significant set bit.
 *
 * fls64(value) returns 0 if value is 0 or the position of the last
 * set bit if value is nonzero. The last (most significant) bit is
 * at position 64.
 */
#if BITS_PER_LONG == 32
static inline int fls64(__u64 x)
{
	__u32 h = x >> 32;
	if (h)
		return fls32(h) + 32;
	return fls(x);
}
#elif BITS_PER_LONG == 64
static inline int fls64(__u64 x)
{
	if (x == 0)
		return 0;
	return __fls(x) + 1;
}
#else
#error BITS_PER_LONG not 32 or 64
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_ASM_FLS64_T */