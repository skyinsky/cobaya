#ifndef _LIBTOOLKIT_CACHE_H
#define _LIBTOOLKIT_CACHE_H

#include <libtoolkit/asm/config.h>

#ifdef __cplusplus
extern "C" {
#endif

/* L1 cache line size */
#define L1_CACHE_SHIFT	(CONFIG_X86_L1_CACHE_SHIFT)
#define L1_CACHE_BYTES	(1 << L1_CACHE_SHIFT)

/* Cache line size */
#define CACHE_LINE_BYTES L1_CACHE_BYTES

/* Cache line mask */
#define CACHE_LINE_MASK (CACHE_LINE_BYTES - 1)

/* Return the first cache-aligned value greater or equal to size. */
#define CACHE_LINE_ROUNDUP(size) \
	(CACHE_LINE_BYTES * ((size + CACHE_LINE_BYTES - 1) / CACHE_LINE_BYTES))

/* Force alignment to cache line. */
#define __cache_aligned __attribute__((__aligned__(CACHE_LINE_BYTES)))

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_CACHE_H */
